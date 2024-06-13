#include "system.h"
#include "graph.h"
#include "sidebar.h"
#include "graphInfo.h"
#include "constants.h"
#include "animate.h"
#include "sidebar.h"
#include <iostream>
#include <SFML/Graphics.hpp>

//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

System::System() : _info(nullptr), _graph(nullptr), _sidebar(SIDE_BAR_LEFT, SIDE_BAR_WIDTH) {}

System::System(GraphInfo* info) : _info(info), _graph(info), _sidebar(SIDE_BAR_LEFT, SIDE_BAR_WIDTH) {}
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void System::set_info(GraphInfo* info)
    {
    _info = info;
    _graph.set_info(info);
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

// Perform a step based on the command
void System::step(int command, GraphInfo* info)
    {
    if (info->_mode == GraphInfo::CARTESIAN)
        {
        // Handle different commands to update the system state in Cartesian mode
        switch (command)
            {
                case 1:
                    info->zoom(ZOOM_STEP);
                    break;
                case 2:
                    info->zoom(1.0f / ZOOM_STEP);
                    break;
                case 3:
                    info->pan(-PAN_STEP, 0.0f);
                    break;
                case 4:
                    info->pan(PAN_STEP, 0.0f);
                    break;
                case 5:
                    info->pan(0.0f, -PAN_STEP);
                    break;
                case 6:
                    info->pan(0.0f, PAN_STEP);
                    break;
                default:
                    cout << "Unknown command" << endl;
                    break;
            }
        }
    else if (info->_mode == GraphInfo::POLAR)
        {
        // Handle different commands to update the system state in Polar mode
        switch (command)
            {
                case 1:
                    info->zoom(ZOOM_STEP);
                    break;
                case 2:
                    info->zoom(1.0f / ZOOM_STEP);
                    break;
                case 3:
                    info->pan(-PAN_STEP, 0.0f);
                    break;
                case 4:
                    info->pan(PAN_STEP, 0.0f);
                    break;
                case 5:
                    info->pan(0.0f, -PAN_STEP);
                    break;
                case 6:
                    info->pan(0.0f, PAN_STEP);
                    break;
                case 7: // Increase a
                    info->adjustA(GraphInfo::A_STEP);
                    break;
                case 8: // Decrease a
                    info->adjustA(-GraphInfo::A_STEP);
                    break;
                case 9: // Increase b
                    info->adjustB(GraphInfo::B_STEP);
                    break;
                case 10: // Decrease b
                    info->adjustB(-GraphInfo::B_STEP);
                    break;
                default:
                    cout << "Unknown command" << endl;
                    break;
            }
        }
    cout << "Updating graph" << endl;
    _graph.update(info);
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/
// Update the graph information
void System::update()
    {
    _graph.update(_info);
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

// Draw the graph and sidebar
void System::draw(sf::RenderWindow& window)
    {
    _graph.draw(window); // Draw the graph

    _sidebar.draw(window); // Draw the sidebar
    }



