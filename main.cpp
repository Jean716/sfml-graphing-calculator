#include <iostream>
#include <SFML/Graphics.hpp>
#include "includes/system.h"
#include "includes/graph.h"
#include "includes/animate.h"
#include "includes/sidebar.h"
//#include "includes/graphInfo.h"
#include "includes/constants.h"
int main()
    {
    Animate animate;
    GraphInfo info;
    animate.set_info(&info);
    animate.run();
    return 0;
    }

