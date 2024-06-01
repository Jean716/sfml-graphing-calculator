#include "function.h"
#include <cmath>
#include <stdexcept>

Function::Function(const string& name) : _name(name) {}

string Function::get_name() const
    {
    return _name;
    }

TokenType Function::type() const
    {
    return TokenType::FUNCTION;
    }

void Function::print(ostream& outs) const
    {
    //outs << "Function(" << _name << ")";
    outs << _name;
    }

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
        return sin(value * M_PI / 180);
        }
    else if (_name == "cos")
        {
        return cos(value * M_PI / 180);
        }
    else if (_name == "tan")
        {
        return tan(value * M_PI / 180);
        }
    else if (_name == "cot")
        {
        return 1 / tan(value * M_PI / 180);
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