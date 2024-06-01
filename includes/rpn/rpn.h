#ifndef RPN_H
#define RPN_H
#include <iostream>
#include <string>

#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/token/token.h"
#include "../../includes/token/operator.h"
#include "../../includes/token/integer.h"

using namespace std;


// used for evaluating the postfix expression
class RPN
    {
    public:
        RPN(Queue<Token*>& postfix) : _postfix(postfix) {}
        void set_input(Queue<Token*>& postfix) { _postfix = postfix; }
        float operator()(float x);
        void printStack(Stack<Token*>& stack)
            {
            Stack<Token*> temp;
            while (!stack.empty())
                {
                Token* t = stack.pop();
                t->print();
                cout << " ";
                temp.push(t);
                }
            while (!temp.empty())
                {
                stack.push(temp.pop());
                }
            }

    private:
        Queue<Token*> _postfix;

    };

#endif 