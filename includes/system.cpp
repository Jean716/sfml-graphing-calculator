#include "system.h"
#include "graph.h"
#include "sidebar.h"
#include "graphInfo.h"
#include "constants.h"
#include "animate.h"
#include "sidebar.h"
#include <iostream>
#include <SFML/Graphics.hpp>



System::System() : _info(nullptr), _graph(nullptr), _sidebar(SIDE_BAR_LEFT, SIDE_BAR_WIDTH) {}

System::System(GraphInfo* info) : _info(info), _graph(info), _sidebar(SIDE_BAR_LEFT, SIDE_BAR_WIDTH) {}

void System::set_info(GraphInfo* info)
    {
    _info = info;
    _graph.set_info(info);
    }

// Perform a step based on the command
void System::step(int command, GraphInfo* info)
    {
    // Handle different commands to update the system state
    switch (command)
        {
            case 1:
                cout << "Zooming in" << endl;
                info->zoom(ZOOM_STEP);
                break;
            case 2:
                cout << "Zooming out" << endl;
                info->zoom(1.0f / ZOOM_STEP);
                break;
            case 3:
                cout << "Moving left" << endl;
                info->pan(-PAN_STEP, 0.0f);
                break;
            case 4:
                cout << "Moving right" << endl;
                info->pan(PAN_STEP, 0.0f);
                break;
            case 5:
                cout << "Moving up" << endl;
                info->pan(0.0f, -PAN_STEP);
                break;
            case 6:
                cout << "Moving down" << endl;
                info->pan(0.0f, PAN_STEP);
                break;
            default:
                cout << "Unknown command" << endl;
                break;
        }

    cout << "Updating graph" << endl;
    _graph.update(info);
    }

// Update the graph information
void System::update()
    {
    _graph.update(_info);
    }

// Draw the graph and sidebar
void System::draw(sf::RenderWindow& window)
    {
    _graph.draw(window); // Draw the graph
    _sidebar.draw(window); // Draw the sidebar
    }


