#include <iostream>
#include <SFML/Graphics.hpp>
#include "includes/system.h"
#include "includes/graph.h"
#include "includes/animate.h"
#include "includes/sidebar.h"
#include "includes/graphInfo.h"
#include "includes/constants.h"
int main()
    {
    GraphInfo graphInfo;
    graphInfo.setEquation("sin(x)");

    Animate animate;
    animate.set_info(&graphInfo);
    animate.run();
    return 0;
    }

