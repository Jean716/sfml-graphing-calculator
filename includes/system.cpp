#include "system.h"
#include "graph.h"
#include "sidebar.h"
#include "graphInfo.h"
#include "constants.h"
#include "animate.h"
#include <iostream>
#include <SFML/Graphics.hpp>



System::System() : _graph(), _info(nullptr), _sidebar(1120, 280)
    {

    }


System::System(GraphInfo* info) : _graph(), _info(info), _sidebar(0, 280)
    {

    }

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
                // Example command: Zoom in
                _info->setScale(_info->getScale() * 1.1f);
                break;
            case 2:
                // Example command: Zoom out
                _info->setScale(_info->getScale() / 1.1f);
                break;
            case 3:
                // Example command: Move left
                _info->setOrigin({ _info->getOrigin().x - 10, _info->getOrigin().y });
                break;
            case 4:
                // Example command: Move right
                _info->setOrigin({ _info->getOrigin().x + 10, _info->getOrigin().y });
                break;
            case 5:
                // Example command: Move up
                _info->setOrigin({ _info->getOrigin().x, _info->getOrigin().y - 10 });
                break;
            case 6:
                // Example command: Move down
                _info->setOrigin({ _info->getOrigin().x, _info->getOrigin().y + 10 });
                break;
            default:
                break;
        }
    update();
    }

// Update the graph information
void System::update()
    {
    // Update the graph with the latest info
    //_graph.update(_info->getEquation());
    }

// Draw the graph and sidebar
void System::draw(sf::RenderWindow& window)
    {
    _graph.draw(window); // Draw the graph
    _sidebar.draw(window); // Draw the sidebar
    }

void System::handleEvent(const sf::Event& event)
    {
    _sidebar.handleEvent(event);
    }
