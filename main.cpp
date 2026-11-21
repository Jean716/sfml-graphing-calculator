#include <cstring>
#include <iostream>
#include "includes/animate.h"
#include "includes/graphInfo.h"
using namespace std;

// Usage:
//   ./bin/main             run the calculator
//   ./bin/main --verbose   also print the internal trace (tokenizer,
//                          shunting yard, RPN evaluation of every point)
int main(int argc, char** argv)
    {
    const bool verbose = argc > 1 && strcmp(argv[1], "--verbose") == 0;

    // The engine traces every step to stdout, which is tens of thousands of
    // lines per redraw. Discard that trace unless it was asked for; errors
    // still go to stderr. (With no buffer, cout drops output cheaply.)
    streambuf* original = cout.rdbuf();
    if (!verbose)
        {
        cout.rdbuf(nullptr);
        }

    GraphInfo graphInfo;
    Animate animate;
    animate.set_info(&graphInfo);
    animate.run();

    cout.rdbuf(original);
    return 0;
    }
