#include <iostream>
#include <SFML/Graphics.hpp>
#include "includes/system.h"
#include "includes/graph.h"
#include "includes/animate.h"
#include "includes/sidebar.h"
#include "includes/graphInfo.h"
#include "includes/constants.h"
using namespace std;
int main()
    {
    try
        {

        GraphInfo graphInfo;
        Animate animate;
        animate.set_info(&graphInfo);
        animate.run();
        }
    catch (const exception& e)
        {
        cerr << "An error occurred: " << e.what() << endl;
        }
    catch (...)
        {
        cerr << "An unknown error occurred." << endl;
        }

    return 0;
    }
