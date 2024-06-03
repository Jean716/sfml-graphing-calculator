#ifndef VARIABLE_H
#define VARIABLE_H

#include "token.h"

class Variable : public Token
    {
    public:
        Variable(const string& name) : _name(name) {}

        TokenType type() const override
            {
            if (_name == "x" || _name == "X")
                {
                return TokenType::VARIABLE;
                }
            else
                {
                throw invalid_argument("Invalid variable name" + _name);
                }

            }

        string get_value() const override
            {
            return _name;



            }

        void print(ostream& outs = cout) const override
            {
            outs << get_value();

            }



    private:
        string _name;
    };

#endif