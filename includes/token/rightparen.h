#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H
#include "token.h"
#include <iostream>


using namespace std;

class RightParen : public Token
    {
    public:
        RightParen() : _name(")") {}
        TokenType type() const override
            {
            if (get_value() == ")")
                {
                return TokenType::RIGHT_PAREN;
                }
            else
                {
                throw invalid_argument("Invalid right parenthesis");

                }
            }
        string get_value() const override { return ")"; }
        void print(ostream& outs = cout) const override { outs << ")"; }



    private:
        string _name = ")";
    };

#endif 