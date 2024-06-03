#ifndef TK_STRING_H
#define TK_STRING_H

#include "token.h"
#include <string>
#include <vector>
#include <iostream>
#include "tk_string.h"
#include "token.h"
using namespace std;
#include <string>
#include <vector>
#include <iostream>

#include "token.h"
#include "integer.h"
#include "operator.h"
#include "function.h"
#include "variable.h"
#include "leftparen.h"
#include "rightparen.h"

class TK_string
    {
    public:

        vector<Token*> split(const string& tk_Str);

    private:
        bool is_number(const string& s) const;
        bool is_operator(const string& s) const;
        bool is_function(const string& s) const;
        bool is_variable(const string& s) const;

    };

#endif // Tk_string_H