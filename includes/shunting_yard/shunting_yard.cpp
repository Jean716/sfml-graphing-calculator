#include "shunting_yard.h"
#include <stdexcept>
#include <string>
#include <cassert>
#include <iomanip>

using namespace std;

int ShuntingYard::precedence(const string& op) const
    {
    if (op == "+" || op == "-")
        {
        return 1;
        }
    else if (op == "*" || op == "/")
        {
        return 2;
        }
    else if (op == "^")
        {
        return 3;
        }
    else if (op == "sin" || op == "cos" || op == "tan" || op == "cot" || op == "sqrt")
        {
        return 4;
        }
    return -1;
    }


bool ShuntingYard::is_left_assoc(const string& op) const
    {
    return op != "^";
    }


Queue<Token*> ShuntingYard::postfix()
    {
    return postfix(_infix);
    }

Queue<Token*> ShuntingYard::postfix(const Queue<Token*>& input) const
    {
    cout << "\n*****SY::ShuntingYard is Fired*****" << endl;

    Queue<Token*> output;
    Stack<Token*> stack;
    Queue<Token*> inputCopy = input;

    while (!inputCopy.empty())
        {
        Token* it = inputCopy.pop();
        TokenType type = it->type();

        switch (type)
            {
                case TokenType::INTEGER:
                case TokenType::VARIABLE:
                case TokenType::CONSTANT:

                    output.push(it);
                    break;

                case TokenType::FUNCTION:
                    stack.push(it);
                    break;

                case TokenType::OPERATOR:
                    while (!stack.empty() && stack.top()->type() == TokenType::OPERATOR)
                        {
                        Token* top = stack.top();
                        if ((precedence(top->get_value()) > precedence(it->get_value())) ||
                            (precedence(top->get_value()) == precedence(it->get_value()) && is_left_assoc(top->get_value())))
                            {
                            output.push(stack.pop());
                            }
                        else
                            {
                            break;
                            }
                        }
                    stack.push(it);
                    break;

                case TokenType::LEFT_PAREN:
                    stack.push(it);
                    break;

                case TokenType::RIGHT_PAREN:
                    while (!stack.empty() && stack.top()->type() != TokenType::LEFT_PAREN)
                        {
                        output.push(stack.pop());
                        }
                    if (stack.empty())
                        {
                        throw invalid_argument("Mismatched parentheses");
                        }
                    stack.pop();
                    if (!stack.empty() && stack.top()->type() == TokenType::FUNCTION)
                        {
                        output.push(stack.pop());
                        }
                    break;

                case TokenType::COMMA:
                    while (!stack.empty() && stack.top()->type() != TokenType::LEFT_PAREN)
                        {
                        output.push(stack.pop());
                        }
                    if (stack.empty() || stack.top()->type() != TokenType::LEFT_PAREN)
                        {
                        throw invalid_argument("Mismatched parentheses");
                        }
                    break;

                default:
                    throw invalid_argument("Unknown token type");
            }
        }

    while (!stack.empty())
        {
        Token* top = stack.top();
        if (top->type() == TokenType::LEFT_PAREN || top->type() == TokenType::RIGHT_PAREN)
            {
            throw invalid_argument("Mismatched parentheses");
            }
        output.push(stack.pop());
        }


    cout << "Postfix Queue: ";
    for (Queue<Token*>::Iterator it = output.begin(); it != output.end(); it++)
        {
        cout << setw(3) << **it;
        }
    cout << endl;

    return output;

    }