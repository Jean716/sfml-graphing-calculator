#include "rightparen.h"

TokenType RightParen::type() const
    {
    return TokenType::RIGHT_PAREN;
    }

string RightParen::get_value() const
    {
    return ")";
    }
void RightParen::print(ostream& outs) const
    {
    // outs << "RightParen" << "()";
    outs << ")";
    }

