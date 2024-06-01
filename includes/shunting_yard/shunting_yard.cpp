#include "shunting_yard.h"
#include <stdexcept>
#include <string>
#include <cassert>

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
    else if (op == "x" || op == "X")
        {

        return 4;
        }
    else if (op == "sin" || op == "cos" || op == "tan" || op == "cot" || op == "sqrt")
        {

        return 5;
        }
    else if (op == "(" || op == ")")
        {

        return 6;
        }


    return 0;
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
    cout << "\n===SY::ShuntingYard is Fired===" << endl;

    Queue<Token*> output;
    Stack<Token*> tempStack;
    Queue<Token*> infixCopy = input;

    while (!infixCopy.empty())
        {
        // Print the contents of infixCopy
        cout << "Current infixCopy: ";
        Queue<Token*> infixCopyCopy = infixCopy; // Make a copy of infixCopy to avoid modifying the original queue
        while (!infixCopyCopy.empty())
            {
            Token* token = infixCopyCopy.pop();
            cout << token->get_value() << " ";
            }
        cout << endl;

        Token* it = infixCopy.pop();
        TokenType type = it->type();

        if (type == TokenType::INTEGER || type == TokenType::VARIABLE)
            {
            output.push(it);
            }
        else if (type == TokenType::OPERATOR)
            {
            Operator* op = static_cast<Operator*>(it);
            while (!tempStack.empty() && tempStack.top()->type() == TokenType::OPERATOR)
                {
                Operator* top = static_cast<Operator*>(tempStack.top());
                if (precedence(op->get_value()) <= precedence(top->get_value()))
                    {
                    output.push(tempStack.pop());
                    }
                else
                    {
                    break;
                    }
                }
            tempStack.push(op);
            }
        else if (type == TokenType::LEFT_PAREN)
            {
            tempStack.push(it);
            }
        else if (type == TokenType::RIGHT_PAREN)
            {
            while (!tempStack.empty() && tempStack.top()->type() != TokenType::LEFT_PAREN)
                {
                output.push(tempStack.pop());
                }
            if (tempStack.empty())
                {
                throw invalid_argument("Mismatched parentheses");
                }
            tempStack.pop(); // pop the left parenthesis from the stack but do not add it to the output queue
            }
        else if (type == TokenType::FUNCTION)
            {
            output.push(it);
            }
        else
            {
            throw invalid_argument("Unknown token type");
            }
        }

    while (!tempStack.empty())
        {
        if (tempStack.top()->type() == TokenType::LEFT_PAREN || tempStack.top()->type() == TokenType::RIGHT_PAREN)
            {
            throw invalid_argument("Mismatched parentheses");
            }
        output.push(tempStack.pop());
        }

    // Debug information
    cout << "Postfix: ";
    Queue<Token*> temp = output; // Copy for printing
    while (!temp.empty())
        {
        Token* t = temp.pop();
        t->print();
        std::cout << " ";
        }
    std::cout << std::endl;

    return output;
    }