// End-to-end tests for the expression engine:
//   string -> TK_string::split -> ShuntingYard::postfix -> RPN(x)
// Expected values are computed with <cmath>.
#include "gtest/gtest.h"
#include <cmath>
#include <sstream>
#include <string>
#include <vector>

#include "token/tk_string.h"
#include "shunting_yard/shunting_yard.h"
#include "rpn/rpn.h"
using namespace std;

namespace {

// Evaluate `expr` at x. The engine prints a trace to stdout/stderr, which is
// silenced here so test output stays readable.
double eval(const string& expr, float x = 0) {
    ostringstream sink;
    streambuf* out = cout.rdbuf(sink.rdbuf());
    streambuf* err = cerr.rdbuf(sink.rdbuf());
    vector<Token*> tokens;
    try {
        TK_string tk;
        tokens = tk.split(expr);
        Queue<Token*> infix;
        for (Token* t : tokens) infix.push(t);
        ShuntingYard sy;
        Queue<Token*> postfix = sy.postfix(infix);
        RPN rpn(postfix);
        double y = rpn(x);
        for (Token* t : tokens) delete t;
        cout.rdbuf(out);
        cerr.rdbuf(err);
        return y;
    } catch (...) {
        for (Token* t : tokens) delete t;
        cout.rdbuf(out);
        cerr.rdbuf(err);
        throw;
    }
}

// Most expressions are evaluated in float, so compare with a relative tolerance.
void expect_value(const string& expr, float x, double expected) {
    double got = 0;
    ASSERT_NO_THROW(got = eval(expr, x)) << expr << " at x = " << x;
    EXPECT_NEAR(got, expected, 1e-4 * max(1.0, fabs(expected))) << expr << " at x = " << x;
}

}  // namespace

// --- Arithmetic, precedence, associativity --------------------------------

TEST(Arithmetic, LeftAssociativeMinusAndDivide) {
    expect_value("x - 1 - 1", 5, 3);
    expect_value("8/2/2", 0, 2);
    expect_value("10 % 3", 0, 1);
}

TEST(Arithmetic, PowerIsRightAssociative) {
    expect_value("2^3^2", 0, 512);  // 2^(3^2), not (2^3)^2 = 64
}

TEST(Arithmetic, PolynomialsAndImplicitMultiplication) {
    expect_value("2x+3", 1, 5);
    expect_value("4x^2 + 2x + 1", 1, 7);
    expect_value("1.5x", 2, 3);
    expect_value("x(x+1)", 2, 6);
    expect_value("(x+1)(x-1)", 3, 8);
    expect_value("x/2x", 4, 8);  // read left to right as (x/2)*x
}

TEST(Arithmetic, LeadingUnaryMinus) {
    expect_value("-x^2", 2, -4);  // -(x^2)
    expect_value("-2^2", 0, -4);
    expect_value("(-x)^2", 3, 9);
    expect_value("x^2", -3, 9);
}

// A unary minus after another operator must not pop that operator.
TEST(Arithmetic, UnaryMinusAfterOperator) {
    expect_value("2*-3", 0, -6);
    expect_value("2^-1", 0, 0.5);
    expect_value("3 - -2", 0, 5);
    expect_value("2*-3+1", 0, -5);   // (2*(-3)) + 1
    expect_value("-3+1", 0, -2);     // (-3) + 1
    expect_value("-x*2", 3, -6);
    expect_value("2^-x^2", 1, 0.5);  // 2^(-(1^2))
    expect_value("--2", 0, 2);
}

// --- Functions and constants ----------------------------------------------

TEST(Functions, SingleArgument) {
    expect_value("-sin(x)", 1, -sin(1.0));
    expect_value("sin(x)*cos(x)", 1, sin(1.0) * cos(1.0));
    expect_value("x*sin(x)", 1, sin(1.0));
    expect_value("2sin(x)", 1, 2 * sin(1.0));
    expect_value("log(100)", 0, log(100.0));  // natural log
    expect_value("sqrt(x^2 + 2)", 1, sqrt(3.0));
    expect_value("abs(-5) + abs(5)", 0, 10);
    expect_value("1/x^2", 2, 0.25);
}

TEST(Functions, Constants) {
    expect_value("2pi", 0, 2 * M_PI);
    expect_value("pi*x", 2, 2 * M_PI);
    expect_value("e^x", 1, M_E);
}

TEST(Functions, MaxMinAlone) {
    expect_value("max(x, 2)", 5, 5);
}

// max/min are emitted at their closing parenthesis, like functions.
TEST(Functions, MaxMinInsideLargerExpression) {
    expect_value("max(10, 20) + min(5, 10)", 0, 25);
    expect_value("max(x, 2)*3", 1, 6);
    expect_value("2max(1, 3)", 0, 6);
    expect_value("max(1, 2)^2", 0, 4);
    expect_value("max(min(x, 4), 0)", 7, 4);   // clamp x to [0, 4]
    expect_value("max(min(x, 4), 0)", -3, 0);
    expect_value("max(x + 1, 2x)", 3, 6);
    expect_value("-min(x, 1)", 5, -1);
    expect_value("max(x, -1)", -3, -1);            // unary minus after a comma
    expect_value("max(min(x, 2), -1)", 5, 2);
    expect_value("max(min(x, 2), -1)", -5, -1);
}

// A value followed by a function, constant or "(" is multiplied.
TEST(Functions, ImplicitMultiplicationBeforeFunction) {
    expect_value("sin(x)cos(x)", 1, sin(1.0) * cos(1.0));
    expect_value("x sin(x)", 1, sin(1.0));
    expect_value("(x+1)sin(x)", 1, 2 * sin(1.0));
    expect_value("2x sin(x)", 1, 2 * sin(1.0));
    expect_value("pi(x+1)", 1, 2 * M_PI);
    expect_value("2pi x", 1, 2 * M_PI);
    expect_value("x pi", 2, 2 * M_PI);
}

// --- Invalid input ---------------------------------------------------------

TEST(InvalidInput, IsRejected) {
    EXPECT_ANY_THROW(eval("sin(x", 1));  // unbalanced parenthesis
    EXPECT_ANY_THROW(eval("2 +"));       // missing operand
    EXPECT_ANY_THROW(eval("y + 1"));     // unknown variable
}

// Division by zero follows IEEE 754 instead of throwing; the plotter skips
// the resulting non-finite points (see plot_test).
TEST(InvalidInput, DivisionByZeroGivesInfOrNaN) {
    double y = 0;
    ASSERT_NO_THROW(y = eval("1/x", 0));
    EXPECT_TRUE(std::isinf(y) && y > 0);
    ASSERT_NO_THROW(y = eval("-1/x", 0));
    EXPECT_TRUE(std::isinf(y) && y < 0);
    ASSERT_NO_THROW(y = eval("0/x", 0));
    EXPECT_TRUE(std::isnan(y));
}
