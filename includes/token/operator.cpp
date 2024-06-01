#include "operator.h"
#include <stdexcept>

#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"


Operator::Operator(const string& op) : _op(op) {}


TokenType Operator::type() const
    {
    return TokenType::OPERATOR;
    }

string Operator::get_value() const
    {
    return _op;
    }

void Operator::print(ostream& outs) const
    {
    // outs << "Operator(" << _op << ")";
    outs << _op;
    }

float Operator::evaluate(float a, float b) const
    {
    if (_op == "+")
        {
        return a + b;
        }
    else if (_op == "-")
        {
        return a - b;
        }
    else if (_op == "*")
        {
        return a * b;
        }
    else if (_op == "/")
        {
        if (b == 0)
            {
            throw invalid_argument("Division by zero");
            }
        return a / b;
        }
    else
        {
        throw invalid_argument("Invalid operator");
        }
    }

