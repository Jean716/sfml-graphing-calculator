#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"



using namespace std;


enum class TokenType
    {
    INTEGER,
    OPERATOR,
    FUNCTION,
    VARIABLE,
    LEFT_PAREN,
    RIGHT_PAREN,
    COMMA,
    CONSTANT
    };

class Token
    {
    public:

        virtual ~Token() = default;
        virtual TokenType type() const = 0;
        virtual string get_value() const = 0;
        virtual void print(ostream& outs = cout) const = 0;

        friend ostream & operator<<(ostream & outs, const Token & t)
            {
            t.print(outs);
            return outs;
            }

    };


#endif 