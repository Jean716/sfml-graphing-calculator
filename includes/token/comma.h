#ifndef COMMA_H
#define COMMA_H

#include "token.h"

class Comma : public Token
    {
    public:
        Comma() {}
        TokenType type() const override
            {
            return TokenType::COMMA;
            }
        string get_value() const override
            {
            return ",";
            }
        void print(ostream& outs = cout) const override
            {
            outs << ",";
            }
    };

#endif // COMMA_H
