#include  "tk_string.h"
#include <iostream>
#include "comma.h"
#include <sstream> // for istringstream


bool TK_string::is_number(const string& s) const
    {
    istringstream iss(s);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();
    }

bool TK_string::is_operator(const string & s) const
    {
    return s == "+" || s == "-" || s == "*" || s == "/" || s == "^" || s == "%" || s == "max" || s == "min";
    }

bool TK_string::is_function(const string & s) const
    {

    return s == "sin" || s == "cos" || s == "tan" || s == "cot" || s == "sqrt" || s == "log" || s == "exp" || s == "abs";
    }

bool TK_string::is_variable(const string & s) const
    {

    return s == "x" || s == "X";
    }



vector<Token*> TK_string::split(const string& tk_Str)
    {
    vector<Token*> tokens; // initialize an empty vector of tokens
    string token;  // initialize an empty string
    int leftParenCount = 0;
    int rightParenCount = 0;

    for (size_t i = 0; i < tk_Str.size(); ++i)
        {
        char c = tk_Str[i]; // get the character at index i

        if (isspace(c))
            { // if the character is a space, skip it
            continue; // skip the rest of the loop and go to the next iteration
            }

        if (isdigit(c) || c == '.')
            { // if the character is a digit or a decimal point
            token += c; // add the character to the token string
            while (i + 1 < tk_Str.size() && (isdigit(tk_Str[i + 1]) || tk_Str[i + 1] == '.'))
                { // while the next character is a digit or a decimal point
                token += tk_Str[++i]; // add the next character to the token string
                }
            tokens.push_back(static_cast<Token*>(new Integer(token))); // add the token to the vector of tokens
            token.clear(); // clear the token string
            }
        else if (isalpha(c))
            { // if the character is a letter
            token += c; // add the character to the token string
            while (i + 1 < tk_Str.size() && isalpha(tk_Str[i + 1]))
                {
                token += tk_Str[++i];
                }
            if (is_function(token))
                {
                tokens.push_back(static_cast<Token*>(new Function(token)));
                }
            else if (is_operator(token))
                { // check if it's a multi-character operator
                tokens.push_back(static_cast<Token*>(new Operator(token)));
                }
            else
                {
                tokens.push_back(static_cast<Token*>(new Variable(token)));
                }
            token.clear();
            }
        else if (c == '(')
            {
            tokens.push_back(static_cast<Token*>(new LeftParen()));
            leftParenCount++;
            }
        else if (c == ')')
            {
            tokens.push_back(static_cast<Token*>(new RightParen()));
            rightParenCount++;
            }
        else if (c == ',')
            {
            tokens.push_back(static_cast<Token*>(new Comma()));
            }
        else if (is_operator(string(1, c)))
            { // check for single character operators
            tokens.push_back(static_cast<Token*>(new Operator(string(1, c))));
            }
        else
            {
            throw invalid_argument("Unknown token: " + string(1, c));
            }
        }

    if (leftParenCount != rightParenCount)
        {
        throw MissingParenthesisException();
        }

    return tokens;
    }
