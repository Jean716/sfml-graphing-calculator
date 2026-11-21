#include "operator.h"
#include <cmath> // for pow
#include <algorithm> // for max and min
#include <stdexcept> // for runtime_error
#include "../../includes/exceptions/dividebyzero.h"

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
        // No exception on b == 0: IEEE 754 gives +/-inf (or NaN for 0/0),
        // and the plotter skips non-finite points. Throwing here aborted
        // the whole redraw whenever one sample landed exactly on x = 0.
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
