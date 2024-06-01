#include  "tk_string.h"
#include <cctype>
#include <sstream>

std::vector<std::string> TK_string::split(const std::string& str)
    {
    std::vector<std::string> tokens;
    std::string token;
    for (size_t i = 0; i < str.size(); ++i)
        {
        char c = str[i];
        if (isdigit(c) || c == '.' || (c == '-' && (i == 0 || str[i - 1] == '(')))
            {
            // Handle numbers and negative numbers
            token += c;
            while (i + 1 < str.size() && (isdigit(str[i + 1]) || str[i + 1] == '.'))
                {
                token += str[++i];
                }
            }
        else if (isalpha(c))
            {
            // Handle functions and variables
            token += c;
            while (i + 1 < str.size() && isalpha(str[i + 1]))
                {
                token += str[++i];
                }
            }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')')
            {
            // Handle operators and parentheses
            if (!token.empty())
                {
                tokens.push_back(token);
                token.clear();
                }
            tokens.push_back(std::string(1, c));
            }
        else
            {
            // Skip unrecognized characters
            if (!token.empty())
                {
                tokens.push_back(token);
                token.clear();
                }
            }
        }
    if (!token.empty())
        {
        tokens.push_back(token);
        }
    return tokens;
    }


