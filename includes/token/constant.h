#ifndef CONSTANT_H
#define CONSTANT_H
#include "token.h"
#include <string>
#include <cmath>
#include <iostream>

class Constant : public Token
    {
    public:
        Constant(const string& value) : _value(value) {} // Constructor
        string get_value() const override { return _value; } // Get the value of the constant

        TokenType type() const override { return TokenType::CONSTANT; }  // Get the type of the constant
        void print(ostream& outs = cout) const override { outs << _value; } // Print the constant
        float get_value_float() const
            {
            if (_value == "pi") return M_PI; // Return the value of pi
            if (_value == "e") return M_E; // Return the value of e
            throw invalid_argument("Unknown constant: " + _value); // Throw an exception if the constant is unknown
            }
    private:
        string _value;
    };

#endif // CONSTANT_H

