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
    LEFT_PAREN,
    RIGHT_PAREN,
    VARIABLE,
    };

class Token
    {
    public:
        Token() = default;
        virtual ~Token() = default;
        Token(const Token& other) : _type(other._type), _value(other._value) {}
        Token& operator=(const Token& other)
            {
            if (this != &other)
                {
                _type = other._type;
                _value = other._value;
                }
            return *this;
            }


        virtual TokenType type() const = 0;
        virtual string get_value() const = 0;
        virtual void print(ostream& outs = cout) const = 0;

        friend ostream & operator<<(ostream & outs, const Token & t)
            {
            t.print(outs);
            return outs;
            }
    private:
        TokenType _type;
        string _value;

    };


#endif 