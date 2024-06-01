#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H
#include "token.h"
#include <iostream>
#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"

using namespace std;


class RightParen : public Token
    {
    public:
        TokenType type() const override;
        string get_value() const override;
        void print(ostream& outs = cout) const override;

    };

#endif 