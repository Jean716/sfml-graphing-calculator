#include "rpn.h"
#include <iostream>
#include <stdexcept> // for runtime_error
#include "/Users/jwcomputer/CS3A_Project/99_00_final_project/includes/exceptions/dividebyzero.h"

using namespace std;


float RPN::operator()(float x)
    {
    try
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
                    Variable* variable_token = static_cast<Variable*>(token);
                    string var_name = variable_token->get_value();
                    if (var_name == "x")
                        stack.push(x);
                    // else if (var_name == "a")
                    //     stack.push(a);
                    // else if (var_name == "b")
                    //     stack.push(b);
                    break;
                    }
                    case TokenType::OPERATOR: {
                    Operator* operator_token = static_cast<Operator*>(token);
                    if (operator_token->isUnary())
                        {
                        if (stack.size() < 1)
                            {
                            throw runtime_error("Insufficient values in expression for unary operator");
                            }
                        float value = stack.pop();
                        stack.push(operator_token->evaluate(value));
                        }
                    else
                        {
                        if (stack.size() < 2)
                            {
                            throw runtime_error("Insufficient values in expression for binary operator");
                            }
                        float right = stack.pop();
                        float left = stack.pop();
                        stack.push(operator_token->evaluate(left, right));
                        }
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
                    case TokenType::CONSTANT: {
                    Constant* constant_token = static_cast<Constant*>(token);
                    stack.push(constant_token->get_value_float());
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
    catch (const exception& e)
        {
        cerr << "An error occurred in RPN::operator(): " << e.what() << endl;
        return 0.0f; // Return a default value in case of error
        }
    catch (const DivideByZero& e)
        {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0.0f; // Return a default value in case of error
        }
    }
