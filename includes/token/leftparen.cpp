
#include "leftparen.h"
#include "token.h"
using namespace std;


TokenType LeftParen::type() const
    {
    return TokenType::LEFT_PAREN;
    }

string LeftParen::get_value() const
    {
    return "(";
    }
void LeftParen::print(ostream& outs) const
    {
    // outs << "LeftParen" << "()";
    outs << "(";
    }

