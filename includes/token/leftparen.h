#ifndef LEFTPAREN_H
#define LEFTPAREN_H
#include "token.h"
#include <iostream>


using namespace std;

class LeftParen : public Token
    {
    public:
        TokenType type() const override;
        string get_value() const override;
        void print(ostream& outs = cout) const override;

    };

#endif
