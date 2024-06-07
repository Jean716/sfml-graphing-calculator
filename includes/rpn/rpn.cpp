#include "rpn.h"
#include <iostream>
#include <stdexcept> // for runtime_error
using namespace std;


float RPN::operator()(float x)
    {
    cout << "\n*****RPN::operator() is Fired*****" << endl;
    Stack<float> stack;
    Queue<Token*> postfix_copy = _postfix; // Make a copy of the postfix queue

    while (!postfix_copy.empty())
        {
        Token* token = postfix_copy.pop();
        TokenType type = token->type();

        switch (type)
            {
                case TokenType::INTEGER: {
                Integer* integer_token = static_cast<Integer*>(token);
                stack.push(integer_token->get_value_float());
                break;
                }
                case TokenType::VARIABLE: {
                stack.push(x);
                break;
                }
                case TokenType::OPERATOR: {
                if (stack.size() < 2)
                    {
                    throw runtime_error("Insufficient values in expression");
                    }
                float right = stack.pop();
                float left = stack.pop();
                Operator* operator_token = static_cast<Operator*>(token);
                stack.push(operator_token->evaluate(left, right));
                break;
                }
                case TokenType::FUNCTION: {
                if (stack.empty())
                    {
                    throw runtime_error("Insufficient values in expression");
                    }
                float value = stack.pop();
                Function* function_token = static_cast<Function*>(token);
                stack.push(function_token->evaluate(value));
                break;
                }
                default: {
                throw runtime_error("Unknown token type");
                }
            }
        }

    if (stack.size() != 1)
        {
        throw runtime_error("The user input has too many values");
        }

    return stack.pop();
    }
