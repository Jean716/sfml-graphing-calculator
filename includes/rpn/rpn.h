#ifndef RPN_H
#define RPN_H
#include <iostream>
#include <string>

#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/token/token.h"
#include "../../includes/token/operator.h"
#include "../../includes/token/integer.h"
#include "../../includes/token/function.h"

using namespace std;


// used for evaluating the postfix expression
class RPN
    {
    public:
        RPN(Queue<Token*>& postfix) : _postfix(postfix) {}
        void set_input(Queue<Token*>& postfix) { _postfix = postfix; }
        float operator()(float x);

    private:
        Queue<Token*> _postfix;

    };

#endif 