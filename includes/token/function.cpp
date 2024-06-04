#include "function.h"
#include <cmath>


string Function::get_value() const
    {
    if (_name == "sin")
        {
        return "sin";
        }
    else if (_name == "cos")
        {
        return "cos";
        }
    else if (_name == "tan")
        {
        return "tan";
        }
    else if (_name == "cot")
        {
        return "cot";
        }
    else if (_name == "sqrt")
        {
        return "sqrt";
        }
    else
        {
        throw runtime_error("Invalid function name");
        }
    }


float Function::evaluate(const float& value) const
    {
    if (_name == "sin")
        {
        return sin(value);
        }
    else if (_name == "cos")
        {
        return cos(value);
        }
    else if (_name == "tan")
        {
        return tan(value);
        }
    else if (_name == "cot")
        {
        return 1 / tan(value);
        }

    else if (_name == "sqrt")
        {
        return sqrt(value);
        }
    else
        {
        throw runtime_error("Invalid function name");
        }
    }