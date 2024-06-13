#include "operator.h"
#include <cmath> // for pow
#include <algorithm> // for max and min
#include <stdexcept> // for runtime_error
#include "/Users/jwcomputer/CS3A_Project/99_00_final_project/includes/exceptions/dividebyzero.h"


float Operator::evaluate(float a, float b) const
    {
    if (_op == "+")
        {
        return a + b;
        }
    else if (_op == "-")
        {
        return a - b;
        }
    else if (_op == "*")
        {
        return a * b;
        }
    else if (_op == "/")
        {
        if (b == 0)
            {
            throw DivideByZero("Division by zero error");
            }
        return a / b;
        }
    else if (_op == "^")
        {
        return pow(a, b);
        }
    else if (_op == "%")
        {
        return fmod(a, b);
        }
    else if (_op == "max")
        {
        return max(a, b);
        }
    else if (_op == "min")
        {
        return min(a, b);
        }
    else
        {
        throw invalid_argument("Invalid operator");
        }
    }

TokenType Operator::type() const
    {
    if (_op == "+" || _op == "-" || _op == "*" || _op == "/" || _op == "^" || _op == "%" || _op == "max" || _op == "min")
        {
        return TokenType::OPERATOR;
        }
    else
        {
        throw invalid_argument("Invalid operator");
        }
    }


float Operator::evaluate(float value) const
    {
    if (_op == "-")
        {
        return -value;
        }
    else
        {
        throw invalid_argument("Invalid unary operator");
        }
    }
