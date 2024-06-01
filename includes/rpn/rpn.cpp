#include "rpn.h"

#include <iostream>
#include <iostream>
#include <stdexcept>
#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/token/token.h"
#include "../../includes/token/operator.h"
#include "../../includes/token/integer.h"
#include "../../includes/token/function.h"
using namespace std;


float RPN::operator()(float x)
    {
    cout << "\n===RPN::operator() is Fired===" << endl;
    Stack<float> stack;
    Queue<Token*> temp = _postfix;

    // 将队列转换为向量以便于迭代
    std::vector<Token*> tokens;
    while (!temp.empty())
        {
        tokens.push_back(temp.pop());
        }

    // 迭代tokens
    for (size_t i = 0; i < tokens.size(); ++i)
        {
        Token* token = tokens[i];
        cout << "RPN::Token: ";
        token->print();
        cout << endl;

        switch (token->type())
            {
                case TokenType::INTEGER: {
                Integer* integer = dynamic_cast<Integer*>(token);
                stack.push(integer->get_value_float());
                cout << "Pushed INTEGER: " << integer->get_value_float() << endl;
                break;
                }
                case TokenType::VARIABLE: {
                stack.push(x);
                cout << "Pushed VARIABLE x: " << x << endl;
                break;
                }
                case TokenType::FUNCTION: {
                Function* func = dynamic_cast<Function*>(token);
                if (i + 1 < tokens.size())
                    {
                    Token* next_token = tokens[++i];
                    if (next_token->type() == TokenType::INTEGER || next_token->type() == TokenType::VARIABLE)
                        {
                        float value = (next_token->type() == TokenType::INTEGER) ?
                            dynamic_cast<Integer*>(next_token)->get_value_float() :
                            x;
                        float result = func->evaluate(value);
                        stack.push(result);
                        cout << "Applied FUNCTION " << func->get_name() << " to " << value << " = " << result << endl;
                        }
                    else
                        {
                        throw std::runtime_error("Unexpected token type after function");
                        }
                    }
                else
                    {
                    throw std::runtime_error("Expected operand after function but none found");
                    }
                break;
                }
                case TokenType::OPERATOR: {
                Operator* op = dynamic_cast<Operator*>(token);
                if (stack.size() < 2)
                    {
                    throw std::runtime_error("Stack does not have enough operands for operator");
                    }
                float right = stack.top();
                stack.pop();
                float left = stack.top();
                stack.pop();
                if (op->get_value() == "+")
                    {
                    stack.push(left + right);
                    cout << "Applied OPERATOR +: " << left << " + " << right << " = " << (left + right) << endl;
                    }
                else if (op->get_value() == "-")
                    {
                    stack.push(left - right);
                    cout << "Applied OPERATOR -: " << left << " - " << right << " = " << (left - right) << endl;
                    }
                else if (op->get_value() == "*")
                    {
                    stack.push(left * right);
                    cout << "Applied OPERATOR *: " << left << " * " << right << " = " << (left * right) << endl;
                    }
                else if (op->get_value() == "/")
                    {
                    stack.push(left / right);
                    cout << "Applied OPERATOR /: " << left << " / " << right << " = " << (left / right) << endl;
                    }
                else if (op->get_value() == "^")
                    {
                    stack.push(std::pow(left, right));
                    cout << "Applied OPERATOR ^: " << left << " ^ " << right << " = " << std::pow(left, right) << endl;
                    }
                else
                    {
                    throw std::runtime_error("Unrecognized operator: " + op->get_value());
                    }
                break;
                }
                default:
                    throw std::runtime_error("Unrecognized token type");
            }
        }

    if (stack.size() != 1)
        {
        throw std::runtime_error("Stack should have exactly one element for the final result");
        }

    return stack.top();
    }
