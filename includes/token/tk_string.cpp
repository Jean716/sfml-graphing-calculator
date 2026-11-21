#include  "tk_string.h"
#include <iostream>
#include "comma.h"
#include <sstream> 
#include "../../includes/exceptions/missingparan.h"
#include "../../includes/exceptions/dividebyzero.h"
bool TK_string::is_number(const string& s) const  // check if the string is a number
    {
    istringstream iss(s);  // create an input string stream
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();  // return true if the stream is at the end and no errors occurred
    }

bool TK_string::is_operator(const string & s) const  // check if the string is an operator
    {
    return s == "+" || s == "-" || s == "*" || s == "/" || s == "^" || s == "%" || s == "max" || s == "min";  // return true if the string is an operator
    }

bool TK_string::is_function(const string & s) const
    {

    return s == "sin" || s == "cos" || s == "tan" || s == "cot" || s == "sqrt" || s == "log" || s == "exp" || s == "abs";
    }

bool TK_string::is_variable(const string & s) const
    {

    return s == "x" || s == "X" || s == "theta" || s == "θ" || s == "a" || s == "b";
    }

bool TK_string::is_constant(const string& s) const
    {
    return s == "pi" || s == "e";
    }

vector<Token*> TK_string::split(const string& tk_Str)
    {
    vector<Token*> tokens;
    string token;
    bool expectUnary = true;
    int leftParenCount = 0;
    int rightParenCount = 0;

    // Implicit multiplication: when a complete value (number, variable,
    // constant or ")") is directly followed by the start of another value
    // (variable, constant, function or "("), insert "*".
    // Examples: 2x, x(x+1), (x+1)(x-1), sin(x)cos(x), x sin(x), pi(x+1)
    auto insert_implicit_multiply = [&tokens]()
        {
        if (tokens.empty())
            {
            return;
            }
        TokenType prev = tokens.back()->type();
        if (prev == TokenType::INTEGER || prev == TokenType::VARIABLE ||
            prev == TokenType::CONSTANT || prev == TokenType::RIGHT_PAREN)
            {
            tokens.push_back(static_cast<Token*>(new Operator("*", false)));
            }
        };

    try
        {
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
                expectUnary = false;
                token.clear();

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
                    insert_implicit_multiply();
                    tokens.push_back(static_cast<Token*>(new Function(token)));

                    if (i + 1 >= tk_Str.size() || tk_Str[i + 1] != '(')
                        {
                        cerr << "Warning: Missing parenthesis for function: " << token << ". Please use the format " << token << "(x)." << endl;
                        throw MissingParan("Mismatched parentheses for function: " + token);
                        }
                    }
                else if (is_operator(token))  // max / min, used like functions
                    {
                    insert_implicit_multiply();
                    tokens.push_back(static_cast<Token*>(new Operator(token, false)));
                    }
                else if (is_constant(token))
                    {
                    insert_implicit_multiply();
                    tokens.push_back(static_cast<Token*>(new Constant(token)));
                    }
                else
                    {
                    insert_implicit_multiply();
                    tokens.push_back(static_cast<Token*>(new Variable(token)));
                    }
                token.clear();
                expectUnary = false;
                }
            else if (c == '(')
                {
                insert_implicit_multiply();
                tokens.push_back(static_cast<Token*>(new LeftParen()));
                leftParenCount++;
                expectUnary = true;
                }
            else if (c == ')')
                {
                tokens.push_back(static_cast<Token*>(new RightParen()));
                rightParenCount++;
                expectUnary = false;
                }
            else if (c == ',')
                {
                tokens.push_back(static_cast<Token*>(new Comma()));
                }
            else if (is_operator(string(1, c)))
                {
                if (c == '-' && expectUnary)
                    {
                    tokens.push_back(static_cast<Token*>(new Operator(string(1, c), true)));
                    }
                else
                    {
                    tokens.push_back(static_cast<Token*>(new Operator(string(1, c), false)));
                    }
                expectUnary = true;
                }
            else
                {
                throw invalid_argument("Unknown token: " + string(1, c));
                }
            }

        if (leftParenCount != rightParenCount)
            {
            throw MissingParan("Mismatched parentheses");
            }
        }
    catch (const MissingParan& e)
        {
        cerr << "Error: " << e.what() << endl;
        throw; // Rethrow the exception to be caught by the caller
        }
    catch (const DivideByZero& e)
        {
        cerr << "Error: " << e.what() << endl;
        throw; // Rethrow the exception to be caught by the caller
        }
    catch (const exception& e)
        {
        cerr << "An error occurred in TK_string::split: " << e.what() << endl;
        throw; // Rethrow the exception to be caught by the caller
        }

    return tokens;
    }

