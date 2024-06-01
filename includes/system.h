#ifndef SYSTEM_H
#define SYSTEM_H

#include <SFML/Graphics.hpp>
#include "graph.h"
#include "graphInfo.h"
#include "sidebar.h"

// this class is to initialize the main window and manage the main loop and  the other interactive objects
class System
    {
    public:
        System();
        System(GraphInfo* info);
        void set_info(GraphInfo* info); //  set the information of the graph
        void step(int command); // handle the command
        void draw(sf::RenderWindow& window); // draw the content of the window
        void update(); //  update the system state
        void handleEvent(const sf::Event& event); //  handle the events on the window object


    private:
        Graph _graph; // manage the graph drawing
        GraphInfo* _info;  // manage the graph information
        Sidebar _sidebar; // manage the sidebar
    };

#endif 
