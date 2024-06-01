#include "integer.h"
#include <stdexcept>
#include <string>
#include <iostream>

Integer::Integer(float value) : _val(value) {}

Integer::Integer(int value) : _val(static_cast<float>(value)) {}

Integer::Integer(const string& value) :_val(stof(value)) {}

Integer::Integer(const char* value) :_val(stof(string(value))) {}

Integer::Integer(char value) : _val(static_cast<float>(value - '0')) {}

Integer::Integer(double value) : _val(static_cast<float>(value)) {}

string Integer::get_value() const
    {
    return to_string(_val);
    }


TokenType Integer::type() const
    {
    return TokenType::INTEGER;
    }

void Integer::print(ostream& outs) const
    {
    //outs << "Integer(" << _val << ")";
    outs << _val;
    }

float Integer::get_value_float() const
    {
    return _val;
    }


