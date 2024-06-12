#include  "tk_string.h"
#include <iostream>
#include "comma.h"
#include <sstream> 
#include "/Users/jwcomputer/CS3A_Project/99_00_final_project/includes/exceptions/missingparan.h"


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

    return s == "x" || s == "X" || s == "theta" || s == "θ";
    }

bool TK_string::is_constant(const string& s) const
    {
    return s == "pi" || s == "e";
    }




vector<Token*> TK_string::split(const string& tk_Str)
    {
    vector<Token*> tokens;
    string token;
    int leftParenCount = 0;
    int rightParenCount = 0;

    for (size_t i = 0; i < tk_Str.size(); ++i)
        {
        char c = tk_Str[i];

        if (isspace(c))
            {
            continue;
            }

        if (isdigit(c) || c == '.')
            {
            token += c;
            while (i + 1 < tk_Str.size() && (isdigit(tk_Str[i + 1]) || tk_Str[i + 1] == '.'))
                {
                token += tk_Str[++i];
                }
            tokens.push_back(static_cast<Token*>(new Integer(token)));
            token.clear();


            if (i + 1 < tk_Str.size() && (isalpha(tk_Str[i + 1]) || tk_Str[i + 1] == '('))
                {
                tokens.push_back(static_cast<Token*>(new Operator("*")));
                }
            }
        else if (isalpha(c))
            {
            token += c;
            while (i + 1 < tk_Str.size() && isalpha(tk_Str[i + 1]))
                {
                token += tk_Str[++i];
                }
            if (is_function(token))
                {
                tokens.push_back(static_cast<Token*>(new Function(token)));

                if (i + 1 >= tk_Str.size() || tk_Str[i + 1] != '(')
                    {
                    cerr << "Warning: Missing parenthesis for function: " << token << ". Please use the format " << token << "(x)." << endl;
                    }
                }
            else if (is_operator(token))
                {
                tokens.push_back(static_cast<Token*>(new Operator(token)));
                }
            else if (is_constant(token))
                {
                tokens.push_back(static_cast<Token*>(new Constant(token)));
                }

            else
                {
                if (!tokens.empty() && (tokens.back()->type() == TokenType::INTEGER || tokens.back()->type() == TokenType::RIGHT_PAREN))
                    {
                    tokens.push_back(static_cast<Token*>(new Operator("*")));
                    }
                tokens.push_back(static_cast<Token*>(new Variable(token)));
                }
            token.clear();
            }
        else if (c == '(')
            {
            if (!tokens.empty() && (tokens.back()->type() == TokenType::INTEGER || tokens.back()->type() == TokenType::VARIABLE || tokens.back()->type() == TokenType::RIGHT_PAREN))
                {
                tokens.push_back(static_cast<Token*>(new Operator("*")));
                }
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
            {
            tokens.push_back(static_cast<Token*>(new Operator(string(1, c))));
            }
        else
            {
            throw invalid_argument("Unknown token: " + string(1, c));
            }
        }

    // if (leftParenCount != rightParenCount)
    //     {
    //     hasParenError = true;
    //     }

    return tokens;
    }