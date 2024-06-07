#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
#include <iostream>
using namespace std;

class DivideByZeroException : public exception
    {
    public:
        const char* what() const noexcept override
            {
            return "Division by zero";
            }
    };

class MissingParenthesisException : public exception
    {
    public:
        const char* what() const noexcept override
            {
            return "Missing parenthesis";
            }
    };

class InvalidOperatorException : public exception
    {
    public:
        InvalidOperatorException(const string& op) : op_(op) {}
        const char* what() const noexcept override
            {
            return "Invalid operator: ";
            }

    private:
        string op_;
    };

#endif // EXCEPTIONS_H
