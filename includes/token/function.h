#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <string>
#include "token.h"



using namespace std;

class Function : public Token  // Function class inherits from Token class
    {
    public:
        Function(const string& name) : _name(name) {} // Constructor
        string get_name() const { return _name; } // Get the name of the function
        TokenType type() const override { return TokenType::FUNCTION; } // Get the type of the function
        void print(ostream& outs = cout) const override { outs << _name; } // Print the function

        string get_value() const override; // Get the value of the function
        float evaluate(const float& value) const; // Evaluate the function

    private:
        string _name;

    };

#endif // FUNCTION_H