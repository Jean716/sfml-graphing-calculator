#ifndef OPERATOR_H
#define OPERATOR_H
#include "token.h"
#include <iostream>
#include <string>



using namespace std;

class Operator : public Token
    {
    public:
        Operator(const string& op);

        string get_value() const override;
        TokenType type() const override;
        void print(ostream& outs = cout) const override;


        void set_precedence(int precedence) { _precedence = precedence; }
        int get_precedence() const { return _precedence; }
        float evaluate(float a, float b) const;



    private:
        string _op;
        int _precedence;
    };

#endif 