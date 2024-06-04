#ifndef SYSTEM_H
#define SYSTEM_H

#include <SFML/Graphics.hpp>
#include "graph.h"
#include "graphInfo.h"
#include "sidebar.h"

// manage domain,zoom,pan,etc
class System
    {
    public:
        System();
        System(GraphInfo* info);

        void set_info(GraphInfo* info); //  set the information of the graph
        void step(int command, GraphInfo* info); // handle the command
        void draw(sf::RenderWindow& window); // draw the content of the window
        void update(); //  update the system state



    private:
        sf::RenderWindow _window; //  window object
        Graph _graph; // manage the graph drawing
        GraphInfo* _info;  // manage the graph information
        Sidebar _sidebar; // manage the sidebar

    };

#endif 