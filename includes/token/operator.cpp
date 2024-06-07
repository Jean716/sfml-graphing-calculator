#include "operator.h"
#include <cmath> // for pow
#include <algorithm> // for max and min
#include <stdexcept> // for runtime_error


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
            throw DivideByZeroException();
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
        throw InvalidOperatorException(_op);
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
        throw InvalidOperatorException(_op);
        }
    }


