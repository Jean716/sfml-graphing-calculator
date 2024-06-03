#ifndef INTEGER_H
#define INTEGER_H

#include <iostream>
#include <string>
#include "token.h"


using namespace std;

class Integer : public Token
    {
    public:
        Integer(float value) : _val(value) {}
        Integer(double value) : _val(value) {}
        Integer(int value) : _val(value) {}
        Integer(const string& value) : _val(stof(value)) {}
        Integer(const char* value) : _val(stof(value)) {}
        Integer(char value) : _val(value) {}

        string get_value() const override { return to_string(_val); }
        float get_value_float() const { return _val; }
        TokenType type() const override { return TokenType::INTEGER; }
        void print(ostream& outs = cout) const override { outs << _val; }

    private:
        float _val;
    };

#endif




