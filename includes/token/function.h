#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <string>
#include "token.h"



using namespace std;

class Function : public Token
    {
    public:
        Function(const string& name) : _name(name) {}
        string get_name() const { return _name; }
        TokenType type() const override { return TokenType::FUNCTION; }
        void print(ostream& outs = cout) const override { outs << _name; }

        string get_value() const override;
        float evaluate(const float& value) const;

    private:
        string _name;

    };

#endif // FUNCTION_H