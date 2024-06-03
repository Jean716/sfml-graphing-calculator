#include  "tk_string.h"
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
    return s == "+" || s == "-" || s == "*" || s == "/" || s == "^";
    }

bool TK_string::is_function(const string & s) const
    {

    return s == "sin" || s == "cos" || s == "tan" || s == "cot" || s == "sqrt";
    }

bool TK_string::is_variable(const string & s) const
    {
    return s == "x" || s == "X";
    }



vector<Token*> TK_string::split(const string& tk_Str)
    {
    vector<Token*> tokens;
    string token;

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
            }
        else if (is_operator(string(1, c)))
            {
            tokens.push_back(static_cast<Token*>(new Operator(string(1, c))));
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
            }
        else if (c == ')')
            {
            tokens.push_back(static_cast<Token*>(new RightParen()));
            }
        else
            {
            throw invalid_argument("Unknown token: " + string(1, c));
            }
        }

    return tokens;
    }
