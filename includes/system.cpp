#include "system.h"
#include "constants.h"
#include "graph.h"
#include "sidebar.h"
#include <functional>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

System::System(const std::function<float(float)>& func) : _graph(func), _sidebar(WORK_PANEL, SIDE_BAR) {}

void System::update()
    {

    }

void System::draw(sf::RenderWindow& window)
    {
    _graph.draw(window); // call the draw function of the graph object
    _sidebar.draw(window); // call the draw function of the sidebar object
    }

Graph& System::getGraph()
    {
    return _graph;
    }

Sidebar& System::getSidebar()
    {
    return _sidebar;
    }