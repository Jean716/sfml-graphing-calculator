#include "animate.h"
#include "constants.h"
#include "system.h"
#include "sidebar.h"
#include "graphInfo.h"
#include <iostream>
#include <string>
using namespace std;

// Constructor
Animate::Animate()
    : _window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Graph Plotter"),
    _mouseIn(false), _sidebar(1120, 280)
    {
    _mousePoint.setRadius(5);
    _mousePoint.setFillColor(sf::Color::Red);

    }
// _system(&_info) // Initialize system with graph info
// {
// // Set mouse point color
// _mousePoint.setFillColor(sf::Color::Red);

// // Load font
// if (!_font.loadFromFile("path/to/font.ttf"))
//     {
//     std::cerr << "Error loading font\n";
//     }

// // Set up text label
// _myTextLabel.setFont(_font);
// _myTextLabel.setString("Mouse Position:");
// _myTextLabel.setCharacterSize(24);
// _myTextLabel.setFillColor(sf::Color::White);
// _myTextLabel.setPosition(10, 10); // Set the position on the screen

// // Set the graph equation to sin(x)
// _info.setEquation("sin(x)");
// _info.setDomain(sf::Vector2f(-10, 10)); // Set the domain
// _info.setScale(50.0f); // Set the scale
// _info.setOrigin(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)); // Set the origin
// }
//
// Run the main loop
void Animate::run()
    {
    while (_window.isOpen())
        {
        processEvents();
        update();
        render();
        }
    }

// Process events (like mouse clicks, key presses)
void Animate::processEvents()
    {
    sf::Event event;
    while (_window.pollEvent(event))
        {
        if (event.type == sf::Event::Closed)
            {
            _window.close();
            }
        _system.handleEvent(event); // Pass event to system
        }
    }
// if (event.type == sf::Event::MouseMoved)
//     {
//     _mouseIn = true;
//     _mousePoint.setPosition(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y);
//     }
// if (event.type == sf::Event::MouseLeft)
//     {
//     _mouseIn = false;
//     }
// // Handle other events like mouse clicks, keyboard presses, etc.
// }

    // Update the state of the system
void Animate::update()
    {
    // Update system objects
    _system.update();

    // // Update text label with current mouse position
    // if (_mouseIn)
    //     {
    //     _myTextLabel.setString("Mouse Position: " + mouse_pos_string(_window));
    //     }
    // else
    //     {
    //     _myTextLabel.setString("Mouse is out of window");
    //     }
    }

// Render everything
void Animate::render()
    {
    _window.clear(sf::Color::White); //  Clear the screen and set a background color
    _system.draw(_window);

    // display the location of the mouse at the left top of the window
    string mousePosStr = mouse_pos_string(_window);
    sf::Text mouseText;
    sf::Font font;
    if (font.loadFromFile("arial.ttf"))
        {
        mouseText.setFont(font);
        mouseText.setString(mousePosStr);
        mouseText.setCharacterSize(20);
        mouseText.setFillColor(sf::Color::Black);
        mouseText.setPosition(10, 10);
        _window.draw(mouseText);
        }

    // Draw the mouse point
    sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
    _mousePoint.setPosition(static_cast<float>(mousePos.x) - _mousePoint.getRadius(), static_cast<float>(mousePos.y) - _mousePoint.getRadius());
    _window.draw(_mousePoint);

    // Draw the sidebar
    _sidebar.draw(_window);

    _window.display();
    }

//Helper function to get mouse position as string
string Animate::mouse_pos_string(sf::RenderWindow & window)
    {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return "(" + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y) + ")";
    }