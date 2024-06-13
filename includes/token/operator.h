#ifndef OPERATOR_H
#define OPERATOR_H
#include "token.h"
#include <iostream>
#include <string>
#include <exception>

using namespace std;

class Operator : public Token
    {
    public:


        Operator(const string& op) : _op(op) {}
        Operator(const string& op, bool unary = false) : _op(op), _unary(unary) {}

        string get_value() const override { return _op; }
        TokenType type() const override;
        void print(ostream& outs = cout) const override { outs << _op; }

        float evaluate(float a, float b) const;
        float evaluate(float a) const;
        bool isUnary() const { return _unary; }


    private:
        string _op;
        bool _unary;
    };

#endif 