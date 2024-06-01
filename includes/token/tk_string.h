#ifndef TK_STRING_H
#define TK_STRING_H

#include "token.h"
#include <string>
#include <vector>
#include <iostream>
#include "tk_string.h"
#include "token.h"
using namespace std;

class TK_string 
    {
    public:
        TK_string(const string& str) : _str(str) {}
       
        static vector<string> split(const string& str);

    private:
        string _str;
    };

#endif 