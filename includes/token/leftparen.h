#ifndef LEFTPAREN_H
#define LEFTPAREN_H
#include "token.h"
#include <iostream>


using namespace std;

class LeftParen : public Token
    {
    public:
        LeftParen() : _name("(") {}
        TokenType type() const override
            {
            if (get_value() == "(")
                {
                return TokenType::LEFT_PAREN;
                }
            else
                {
                throw invalid_argument("Invalid left parenthesis");
                }
            }

        string get_value() const override { return _name; }
        void print(ostream& outs = cout) const override { outs << "("; }

    private:
        string _name = "(";

    };

#endif
