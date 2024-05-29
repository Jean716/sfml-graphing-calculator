#ifndef SYSTEM_H
#define SYSTEM_H

#include <SFML/Graphics.hpp>
#include "graph.h"
#include "sidebar.h"
#include <functional> // for std::function
using namespace std;

// manage domain and range of the graph
class System
    {
    public:
        System(const function<float(float)>& func);
        void update();
        void draw(sf::RenderWindow& window);
        Graph& getGraph();
        //void Step(int command);
        Sidebar& getSidebar();

    private:
        Graph _graph; // This is the graph object that will be used to draw the graph
        Sidebar _sidebar;
    };


#endif