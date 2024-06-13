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
#include <iomanip>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

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
    // _myTextLabel.setFont(_font);
    // _myTextLabel.setCharacterSize(20);
    // _myTextLabel.setFillColor(sf::Color::Black);
    // _myTextLabel.setPosition(10, 10);

    // math coords text
    _coordLabel.setFont(_font);
    _coordLabel.setCharacterSize(20);
    _coordLabel.setFillColor(sf::Color::Black);
    _coordLabel.setPosition(10, 40);

    _coordTranslation.set_info(_info);

    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

// Run the main loop
void Animate::run()
    {
    while (_window.isOpen())
        {
        try
            {
            processEvents();
            update();
            render();
            }
        catch (const exception& e)
            {
            cerr << "An error occurred: " << e.what() << endl;
            // Display error message to user (optional)
            sf::Text errorText;
            errorText.setFont(_font);
            errorText.setCharacterSize(20);
            errorText.setFillColor(sf::Color::Red);
            errorText.setString("Error: " + string(e.what()));
            errorText.setPosition(10, 70); // Position below other labels
            _window.draw(errorText);
            _window.display();

            }
        catch (...)
            {
            cerr << "An unknown error occurred." << endl;
            // Display generic error message to user (optional)
            sf::Text errorText;
            errorText.setFont(_font);
            errorText.setCharacterSize(20);
            errorText.setFillColor(sf::Color::Red);
            errorText.setString("Unknown error occurred.");
            errorText.setPosition(10, 70); // Position below other labels
            _window.draw(errorText);
            _window.display();

            }
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

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

        if (_info->_mode == GraphInfo::INPUT)
            {
            continue;
            }

        if (event.type == sf::Event::KeyPressed)
            {


            cout << "Key pressed: " << event.key.code << endl;

            switch (event.key.code)
                {
                    case sf::Keyboard::RBracket:
                        _system.step(1, _info); // zoom in
                        break;
                    case sf::Keyboard::LBracket:
                        _system.step(2, _info); // zoom out
                        break;
                    case sf::Keyboard::Left:
                        _system.step(3, _info); // move left
                        break;
                    case sf::Keyboard::Right:
                        _system.step(4, _info); // move right
                        break;
                    case sf::Keyboard::Up:
                        _system.step(5, _info); // move up
                        break;
                    case sf::Keyboard::Down:
                        _system.step(6, _info); // move down
                        break;
                    case sf::Keyboard::Tab:
                        _isPolarMode = !_isPolarMode;
                        _info->_mode = _isPolarMode ? GraphInfo::POLAR : GraphInfo::CARTESIAN;
                        break;
                    case sf::Keyboard::A: // press A key to increase a
                        _system.step(7, _info);
                        break;
                    case sf::Keyboard::D: // press Z key to decrease a
                        _system.step(8, _info);
                        break;
                    case sf::Keyboard::W: // press S key to increase b
                        _system.step(9, _info);
                        break;
                    case sf::Keyboard::E: // press X key to decrease b
                        _system.step(10, _info);
                        break;
                    default:
                        break;
                }
            }
        }

    update();
    render();

    }

//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

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
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/
// Render everything
void Animate::render()
    {
    _window.clear(sf::Color(236, 236, 236)); //  Clear the screen and set a background color

    if (_info->_mode == GraphInfo::POLAR)
        {
        drawPolarDomainAndCoordinates(_window);
        _polar.drawPolarGrid(_window, _info);
        _polar.drawPolarLabels(_window, _info);
        if (_info->_history.size() > 0 && _info->_history[0].find("a") != std::string::npos && _info->_history[0].find("b") != std::string::npos)
            {
            _polar.drawRoseCurve(_window, _info);
            }
        else
            {
            _polar.draw(_window, _info);
            }
        }
    else
        {
        _graph.drawGrid(_window);
        _graph.draw(_window);
        drawCartesianDomainAndCoordinates(_window);
        }

    _sidebar.draw(_window);
    _window.display();
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

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
    _polar.set_info(_info);

    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/
void Animate::drawCartesianDomainAndCoordinates(sf::RenderWindow& window)
    {
    // Display the domain information for Cartesian mode
    sf::Text domainText;
    domainText.setFont(_font);
    domainText.setCharacterSize(20);
    domainText.setFillColor(sf::Color::Black);
    sf::Vector2f domain = _info->_domain;

    // Set the precision of the domain text
    ostringstream domainStream;
    domainStream << fixed << setprecision(0) << "[" << domain.x << ", " << domain.y << "]";
    domainText.setString("Domain: " + domainStream.str());
    domainText.setPosition(10, 10);
    window.draw(domainText);

    // get the screen coordinates of the mouse
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    // convert to math coordinates
    sf::Vector2f mathPos = _coordTranslation.getMathCoords(mousePosFloat);

    // set the precision of the math coordinates
    ostringstream oss;
    oss.precision(0);
    oss << fixed << "(" << mathPos.x << ", " << mathPos.y << ")";
    string mathPosStr = oss.str();

    _coordLabel.setString("Cartesian Coordinate: " + mathPosStr);
    _window.draw(_coordLabel);

    // Convert math coordinates back to screen coordinates to ensure the red dot stays at the correct position
    sf::Vector2f screenPos = _coordTranslation.translate(mathPos);
    _mousePoint.setPosition(screenPos.x - _mousePoint.getRadius(), screenPos.y - _mousePoint.getRadius());
    _window.draw(_mousePoint);
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/
void Animate::drawPolarDomainAndCoordinates(sf::RenderWindow& window)
    {
    // check if the font is loaded
    sf::Font font;
    if (!font.loadFromFile("DejaVuSans.ttf"))
        {
        cerr << "Error loading font" << endl;
        }
    sf::Text domainText;
    domainText.setFont(font);
    domainText.setCharacterSize(20);
    domainText.setFillColor(sf::Color::Black);

    sf::Vector2f domain = _info->_domain;

    // set the precision of the domain text
    std::wstring wstr = L"Polar Domain: [0, 2π]";
    domainText.setString(sf::String(wstr));
    domainText.setPosition(10, 10);
    window.draw(domainText);

    // get the screen coordinates of the mouse
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    sf::Vector2f mathPos = _coordTranslation.getPolarCoords(mousePosFloat);

    // set the precision of the math coordinates
    ostringstream oss;
    oss.precision(0);
    oss << fixed << "(" << mathPos.x << ", " << mathPos.y << ")";
    std::string mathPosStr = oss.str();

    sf::Text coordText;
    coordText.setFont(font);
    coordText.setCharacterSize(20);
    coordText.setFillColor(sf::Color::Black);
    coordText.setString("Polar Coordinate: " + mathPosStr);
    coordText.setPosition(10, 40);
    window.draw(coordText);


    sf::Vector2f screenPos = _coordTranslation.translate(mathPos);
    _mousePoint.setPosition(screenPos.x - _mousePoint.getRadius(), screenPos.y - _mousePoint.getRadius());
    window.draw(_mousePoint);
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/
