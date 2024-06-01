#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <string>
#include <cmath>
#include "token.h"



using namespace std;

class Function : public Token
    {
    public:
        Function(const string& name);
        string get_name() const;

        string get_value() const override;
        TokenType type() const override;
        void print(ostream& outs = cout) const override;

        float evaluate(const float& value) const;



    private:
        string _name;

    };

#endif 