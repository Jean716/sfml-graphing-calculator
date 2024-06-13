#ifndef COMMA_H
#define COMMA_H

#include "token.h"

class Comma : public Token // Comma class inherits from Token class
    {
    public:
        Comma() {}
        TokenType type() const override // override the type function
            {
            return TokenType::COMMA;
            }
        string get_value() const override // override the get_value function
            {
            return ",";
            }
        void print(ostream& outs = cout) const override // override the print function
            {
            outs << ",";
            }
    };

#endif // COMMA_H
