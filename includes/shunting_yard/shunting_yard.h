#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/operator.h"
#include "../token/integer.h"
#include "../token/function.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"
#include "../exceptions/missingparan.h"
#include "../token/variable.h"
#include "../token/comma.h"
#include "../token/constant.h"


using namespace std;

class ShuntingYard
    {
    private:

        Queue<Token*> _infix;

        int precedence(const string& op) const;
        bool is_left_assoc(const string& op) const;


    public:
        ShuntingYard() {}
        ShuntingYard(Queue<Token*>& input) : _infix(input) {}

        Queue<Token*> postfix(); // no arguments and uses the _infix member variable
        Queue<Token*> postfix(const Queue<Token*>& input) const; // takes another Queue<Token*> as an argument

        void infix(Queue<Token*>& input) { _infix = input; }


    };

#endif