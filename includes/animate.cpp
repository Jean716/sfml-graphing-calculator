#include "animate.h"
#include "constants.h"
#include "system.h"
#include "sidebar.h"
#include "graphInfo.h"
#include "coord_translation.h"
#include <iostream>
#include <string>
#include <sstream> 
#include <SFML/Graphics.hpp>

using namespace std;

// Constructor
Animate::Animate()
    : _window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Graphing Calculator"),
    _system(), _sidebar(WORK_PANEL, SIDE_BAR_WIDTH), _mouseIn(false),
    _mousePoint(5.0f), _font(), _myTextLabel(), _coordLabel(), _coordTranslation(nullptr)
    {

    _mousePoint.setRadius(2);
    _mousePoint.setFillColor(sf::Color::Red);
    if (!_font.loadFromFile("arial.ttf"))
        {
        // handel error
        }
    // screen coords text
    _myTextLabel.setFont(_font);
    _myTextLabel.setCharacterSize(20);
    _myTextLabel.setFillColor(sf::Color::White);
    _myTextLabel.setPosition(10, 10);
    // math coords text
    _coordLabel.setFont(_font);
    _coordLabel.setCharacterSize(20);
    _coordLabel.setFillColor(sf::Color::White);
    _coordLabel.setPosition(10, 40);

    _coordTranslation.set_info(_info);

    }

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

        _sidebar.handleEvent(event, _info); // Pass event to sidebar

        if (event.type == sf::Event::KeyPressed)
            {
            cout << "Key pressed: " << event.key.code << endl;

            switch (event.key.code)
                {
                    case sf::Keyboard::Equal:
                        _system.step(1, _info); // zoom in
                        break;
                    case sf::Keyboard::Hyphen:
                        _system.step(2, _info); // zoom out
                        break;
                    case sf::Keyboard::A:
                        _system.step(3, _info); // move left
                        break;
                    case sf::Keyboard::D:
                        _system.step(4, _info); // move right
                        break;
                    case sf::Keyboard::W:
                        _system.step(5, _info); // move up
                        break;
                    case sf::Keyboard::S:
                        _system.step(6, _info); // move down
                        break;
                    default:
                        break;
                }
            }
        update();
        render();

        }
    }

// Update the state of the system
void Animate::update()
    {
    _system.update();// Update system objects
    if (_mouseIn)
        {
        _coordLabel.setString(mouse_pos_string(_window));
        }
    }

// Render everything
void Animate::render()
    {
    _window.clear(sf::Color(34, 37, 42)); //  Clear the screen and set a background color
    _system.draw(_window); // Draw all objects in system

    // display the location of the mouse at the left top of the window
    string mousePosStr = mouse_pos_string(_window);
    _myTextLabel.setString("Screen Coords: " + mousePosStr);
    _myTextLabel.setPosition(10, 10);
    _window.draw(_myTextLabel);

    // get the screen coordinates of the mouse
    sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
    sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    // convert to math coordinates
    sf::Vector2f mathPos = _coordTranslation.getMathCoords(mousePosFloat);

    // set the precision of the math coordinates
    ostringstream oss;
    oss.precision(0);
    oss << fixed << "(" << mathPos.x << ", " << mathPos.y << ")";
    string mathPosStr = oss.str();

    _coordLabel.setString("Math Coords: " + mathPosStr);
    _window.draw(_coordLabel);

    // drea the little red dot
    _mousePoint.setPosition(mousePosFloat.x - _mousePoint.getRadius(), mousePosFloat.y - _mousePoint.getRadius());
    _window.draw(_mousePoint);
    //_window.draw(_myTextLabel);

    // Draw the sidebar
    _sidebar.draw(_window);
    // check if there is a paren error
    if (_info->hasParenError)
        {
        sf::Text errorMsg;
        errorMsg.setFont(_font);
        errorMsg.setCharacterSize(20);
        errorMsg.setFillColor(sf::Color::Red);
        errorMsg.setString("Error: Mismatched parentheses. Please check your input.");
        errorMsg.setPosition(10, SCREEN_HEIGHT - 30);
        _window.draw(errorMsg);
        }

    _window.display();
    }

//Helper function to get mouse position as string
string Animate::mouse_pos_string(sf::RenderWindow & window)
    {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    return "(" + to_string(mousePos.x) + ", " + to_string(mousePos.y) + ")";
    }

void Animate::set_info(GraphInfo * info)
    {
    cout << "Animat:: set_info is fired" << endl;
    _info = info;
    _system.set_info(info);
    _coordTranslation.set_info(_info);
    }