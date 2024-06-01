#ifndef INTEGER_H
#define INTEGER_H

#include <iostream>
#include <string>
#include "token.h"


using namespace std;

class Integer : public Token
    {
    public:
        Integer(float value);
        Integer(double value);
        Integer(int value);
        Integer(const string& value);
        Integer(const char* value); // char* means a string of characters
        Integer(char value);

        string get_value() const override;
        float get_value_float() const;
        TokenType type() const override;
        void print(ostream& outs = cout) const override;

    private:
        float _val;
    };

#endif




