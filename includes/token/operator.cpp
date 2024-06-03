#include "operator.h"
#include <cmath> // for pow

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
            throw runtime_error("Division by zero");
            }
        return a / b;
        }
    else if (_op == "^")
        {
        return pow(a, b);
        }
    else
        {
        throw invalid_argument("Invalid operator" + _op);
        }
    }

