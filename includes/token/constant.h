#ifndef CONSTANT_H
#define CONSTANT_H
#include "token.h"
#include <string>
#include <cmath>
#include <iostream>

class Constant : public Token
    {
    public:
        Constant(const string& value) : _value(value) {}
        string get_value() const override { return _value; }
        TokenType type() const override { return TokenType::CONSTANT; }
        void print(ostream& outs = cout) const override { outs << _value; }
        float get_value_float() const
            {
            if (_value == "pi") return M_PI;
            if (_value == "e") return M_E;
            throw invalid_argument("Unknown constant: " + _value);
            }
    private:
        string _value;
    };

#endif // CONSTANT_H

