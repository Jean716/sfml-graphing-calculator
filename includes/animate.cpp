#include "animate.h"
#include "constants.h"
#include "system.h"
#include "sidebar.h"
#include "graphInfo.h"
#include "polar.h"
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
    _mousePoint(5.0f), _font(), _myTextLabel(), _coordLabel(),
    _coordTranslation(nullptr), _isPolarMode(false)
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
    _myTextLabel.setFillColor(sf::Color::Black);
    _myTextLabel.setPosition(10, 10);
    // math coords text
    _coordLabel.setFont(_font);
    _coordLabel.setCharacterSize(20);
    _coordLabel.setFillColor(sf::Color::Black);
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
        _sidebar.handleEvent(event, _info);

        if (_info->getMode() == GraphInfo::INPUT)
            {
            continue;
            }

        if (event.type == sf::Event::KeyPressed)
            {
            cout << "Key pressed: " << event.key.code << endl;

            switch (event.key.code)
                {
                    case sf::Keyboard::RBracket:
                        //_info->setMode(GraphInfo::ZOOM);
                        _info->zoom(1.1f);
                        //_system.step(1, _info); // zoom in
                        break;
                    case sf::Keyboard::LBracket:
                        // _info->setMode(GraphInfo::ZOOM);
                        _info->zoom(0.9f);
                        //_system.step(2, _info); // zoom out
                        break;
                    case sf::Keyboard::Left:
                        _info->setMode(GraphInfo::PAN);
                        _system.step(3, _info); // move left
                        break;
                    case sf::Keyboard::Right:
                        _info->setMode(GraphInfo::PAN);
                        _system.step(4, _info); // move right
                        break;
                    case sf::Keyboard::Up:
                        _info->setMode(GraphInfo::PAN);
                        _system.step(5, _info); // move up
                        break;
                    case sf::Keyboard::Down:
                        _info->setMode(GraphInfo::PAN);
                        _system.step(6, _info); // move down
                        break;
                    case sf::Keyboard::Tab:
                        _isPolarMode = !_isPolarMode;
                        _info->setMode(_isPolarMode ? GraphInfo::POLAR : GraphInfo::CARTESIAN);
                        cout << "Mode toggled to: " << (_info->getMode() == GraphInfo::CARTESIAN ? "CARTESIAN" : "POLAR") << endl;
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
    _graph.update(_info); // Ensure _info is passed correctly

    }

// Render everything
void Animate::render()
    {
    _window.clear(sf::Color(236, 236, 236)); //  Clear the screen and set a background color
    if (_info->getMode() == GraphInfo::POLAR)
        {
        _polar.draw(_window, _info);
        _polar.drawPolarLabels(_window, _info);

        }
    else
        {
        drawGrid(_window);
        _graph.draw(_window);
        }

    //_system.draw(_window); // Draw all objects in system


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


    // Convert math coordinates back to screen coordinates to ensure the red dot stays at the correct position
    sf::Vector2f screenPos = _coordTranslation.translate(mathPos);
    _mousePoint.setPosition(screenPos.x - _mousePoint.getRadius(), screenPos.y - _mousePoint.getRadius());
    _window.draw(_mousePoint);

    // if (_info->getMode() == GraphInfo::POLAR)
    //     {
    //     _polar.draw(_window, _info);
    //     }
    // else
    //     {
    //     drawGrid(_window);
    //     _graph.draw(_window);
    //     _system.draw(_window);
    //     }


    // Draw the sidebar
    _sidebar.draw(_window);
    // check if there is a paren error

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

void Animate::drawGrid(sf::RenderWindow& window)
    {
    sf::VertexArray lines(sf::Lines);

    const float step = _info->getScale();
    const sf::Color gridColor(200, 200, 200);

    sf::Vector2f origin = _info->getOrigin();
    float offsetX = _info->getOffsetX();
    float offsetY = _info->getOffsetY();
    float scale = _info->getScale();


    for (float x = origin.x + offsetX; x < WORK_PANEL; x += step)
        {
        lines.append(sf::Vertex(sf::Vector2f(x, 0), gridColor));
        lines.append(sf::Vertex(sf::Vector2f(x, SCREEN_HEIGHT), gridColor));
        }
    for (float x = origin.x + offsetX; x > 0; x -= step)
        {
        lines.append(sf::Vertex(sf::Vector2f(x, 0), gridColor));
        lines.append(sf::Vertex(sf::Vector2f(x, SCREEN_HEIGHT), gridColor));
        }


    for (float y = origin.y + offsetY; y < SCREEN_HEIGHT; y += step)
        {
        lines.append(sf::Vertex(sf::Vector2f(0, y), gridColor));
        lines.append(sf::Vertex(sf::Vector2f(WORK_PANEL, y), gridColor));
        }
    for (float y = origin.y + offsetY; y > 0; y -= step)
        {
        lines.append(sf::Vertex(sf::Vector2f(0, y), gridColor));
        lines.append(sf::Vertex(sf::Vector2f(WORK_PANEL, y), gridColor));
        }

    window.draw(lines);
    }

