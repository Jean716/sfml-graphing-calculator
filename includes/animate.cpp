#include "font.h"
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
#include <thread> // std::this_thread::sleep_for
#include <SFML/Graphics.hpp>


using namespace std;
//*------------------------------------------------------- Constructor-------------------------------------------------------*/
Animate::Animate() // initialize the window, system, sidebar, and graph etc.
    : _window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Graphing Calculator"),
    _system(), _sidebar(WORK_PANEL, SIDE_BAR_WIDTH), _mouseIn(false),
    _mousePoint(5.0f), _font(), _myTextLabel(), _coordLabel(),
    _coordTranslation(nullptr), _isPolarMode(false)
    {

    _mousePoint.setRadius(2); // set the radius of the mouse point
    _mousePoint.setFillColor(sf::Color::Red); // set the color of the mouse point

    _font = app_font();  // shared font, loaded once

    // show the math coordinates on the left top corner
    _coordLabel.setFont(_font);  // set the font of the text
    _coordLabel.setCharacterSize(20); // set the size of the text
    _coordLabel.setFillColor(sf::Color::Black); // set the color of the text
    _coordLabel.setPosition(10, 40); // set the position of the text
    _coordTranslation.set_info(_info); // set the information of the graph

    }
//*------------------------------------------------------- Run（）-------------------------------------------------------*/
void Animate::run()  // run the main loop
    {
    while (_window.isOpen())
        {
        try
            {
            processEvents();  // process the events
            update();  // update the system state
            render();  // render the graphics
            }

        catch (const DivideByZero& e)
            {
            std::cerr << "Caught DivideByZero exception in Animate::run: " << e.what() << std::endl;
            showErrorMessage("Error: " + std::string(e.what()));  // show the error message

            }
        catch (const exception& e)  // catch the exception
            {
            cerr << "An error occurred: " << e.what() << endl;  // handle the error
            showErrorMessage("Error: " + std::string(e.what()));  // show the error message


            }
        catch (...)
            {
            cerr << "An unknown error occurred." << endl;  // handle the error
            showErrorMessage("Unknown error occurred.");  // show the error message



            }
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/
// Display error message
void Animate::showErrorMessage(const string& message)  // show error message
    {
    sf::Text errorText;  // create a text object
    errorText.setFont(_font);  // set the font of the text
    errorText.setCharacterSize(20);  // set the size of the text
    errorText.setFillColor(sf::Color::Red);  // set the color of the text
    errorText.setString(message);  // set the text of the label
    errorText.setPosition(10, 70); // Position below other labels

    // Draw the error message on top of the current content
    _window.draw(errorText);
    _window.display();

    // Add a delay to prevent flickering
    this_thread::sleep_for(chrono::milliseconds(2000)); // 2 seconds delay
    inputDisabled = false;
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

        if (event.type == sf::Event::KeyPressed)
            {
            inputDisabled = true; // Disable input handling on key press
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

                    // V/F/G/D adjust the rose-curve parameters, but only while
                    // the input box is empty; otherwise they are typed as text
                    // (e.g. the "g" in log).
                    case sf::Keyboard::V:
                    case sf::Keyboard::F:
                    case sf::Keyboard::G:
                    case sf::Keyboard::D:
                        if (!_sidebar.isInputEmpty())
                            {
                            inputDisabled = false;
                            break;
                            }
                        if (event.key.code == sf::Keyboard::V) _system.step(7, _info);       // increase a
                        else if (event.key.code == sf::Keyboard::F) _system.step(8, _info);  // decrease a
                        else if (event.key.code == sf::Keyboard::G) _system.step(9, _info);  // increase b
                        else _system.step(10, _info);                                        // decrease b
                        break;
                    default:
                        inputDisabled = false; // Allow input handling for other keys
                        break;
                }
            }
        else if (event.type == sf::Event::KeyReleased)
            {
            inputDisabled = false; // Re-enable input handling on key release
            }

        if (!inputDisabled)
            {
            _sidebar.handleEvent(event, _info); // Handle sidebar events if input is not disabled
            }
        }

    update();  // Update the system
    render();  // Render the graphics
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

    // based on the mode, draw the graph
    if (_info->_mode == GraphInfo::POLAR)
        {
        drawPolarDomainAndCoordinates(_window);  // draw polar domain and coordinates
        _polar.drawPolarGrid(_window, _info);  // draw polar grid
        _polar.drawPolarLabels(_window, _info);  // draw polar labels
        if (_info->_history.size() > 0 && _info->_history[0].find("a") != string::npos && _info->_history[0].find("b") != string::npos)
            {
            _polar.drawRoseCurve(_window, _info);  // draw rose curve
            }
        else
            {
            _polar.draw(_window, _info);  // draw polar
            }
        }
    else
        {
        _graph.drawGrid(_window);  // draw grid
        _graph.draw(_window);  // draw graph
        drawCartesianDomainAndCoordinates(_window);  // draw cartesian domain and coordinates
        }

    _sidebar.draw(_window);  // draw sidebar
    _window.display();   // display the window
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

//Helper function to get mouse position as string
string Animate::mouse_pos_string(sf::RenderWindow & window)    // get mouse position as string
    {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);  // get the mouse position

    return "(" + to_string(mousePos.x) + ", " + to_string(mousePos.y) + ")";  // return the mouse position
    }

void Animate::set_info(GraphInfo * info)  // set the information of the graph
    {
    cout << "Animat:: set_info is fired" << endl;
    _info = info;  // set the information of the graph
    _system.set_info(info);  // set the information of the system
    _coordTranslation.set_info(_info);  // set the information of the coordinate translation
    _polar.set_info(_info);  // set the information of the polar

    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/
void Animate::drawCartesianDomainAndCoordinates(sf::RenderWindow& window)
    {
    // Display the domain information for Cartesian mode
    sf::Text domainText;  // create a text object
    domainText.setFont(_font);  // set the font of the text
    domainText.setCharacterSize(20);  // set the size of the text
    domainText.setFillColor(sf::Color::Black);  // set the color of the text
    sf::Vector2f domain = _info->_domain;  // get the domain of the graph

    // Set the precision of the domain text
    ostringstream domainStream;  // create a string stream
    domainStream << fixed << setprecision(0) << "[" << domain.x << ", " << domain.y << "]";
    domainText.setString("Domain: " + domainStream.str());
    domainText.setPosition(10, 10);  // set the position of the text
    window.draw(domainText);  // draw the text

    // get the screen coordinates of the mouse
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    // convert to math coordinates
    sf::Vector2f mathPos = _coordTranslation.getMathCoords(mousePosFloat);

    // set the precision of the math coordinates
    ostringstream oss;  // create a string stream
    oss.precision(0);  // set the precision of the string stream
    oss << fixed << "(" << mathPos.x << ", " << mathPos.y << ")";  // set the math coordinates
    string mathPosStr = oss.str();  // convert the string stream to string

    _coordLabel.setString("Cartesian Coordinate: " + mathPosStr);  // set the text of the label
    _window.draw(_coordLabel);  // draw the label

    // Convert math coordinates back to screen coordinates to ensure the red dot stays at the correct position
    sf::Vector2f screenPos = _coordTranslation.translate(mathPos);
    _mousePoint.setPosition(screenPos.x - _mousePoint.getRadius(), screenPos.y - _mousePoint.getRadius());
    _window.draw(_mousePoint);
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/
void Animate::drawPolarDomainAndCoordinates(sf::RenderWindow& window)
    {
    // check if the font is loaded
    const sf::Font& font = app_font();  // shared font, loaded once
    sf::Text domainText;  // create a text object
    domainText.setFont(font);  // set the font of the text
    domainText.setCharacterSize(20);  // set the size of the text
    domainText.setFillColor(sf::Color::Black);  // set the color of the text

    sf::Vector2f domain = _info->_domain;  // get the domain of the graph

    // set the precision of the domain text
    wstring wstr = L"Polar Domain: [0, 2π]";  // set the domain text
    domainText.setString(sf::String(wstr));  // set the text of the label
    domainText.setPosition(10, 10);  // set the position of the text
    window.draw(domainText);  // draw the text

    // get the screen coordinates of the mouse
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);  // get the mouse position
    sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    sf::Vector2f mathPos = _coordTranslation.getPolarCoords(mousePosFloat);  // convert to math coordinates

    // set the precision of the math coordinates
    ostringstream oss;  // create a string stream
    oss.precision(0);  // set the precision of the string stream
    oss << fixed << "(" << mathPos.x << ", " << mathPos.y << ")";
    string mathPosStr = oss.str();  // convert the string stream to string

    sf::Text coordText;  // create a text object
    coordText.setFont(font);  // set the font of the text
    coordText.setCharacterSize(20);  // set the size of the text
    coordText.setFillColor(sf::Color::Black);  // set the color of the text
    coordText.setString("Polar Coordinate: " + mathPosStr);  // set the text of the label
    coordText.setPosition(10, 40);  // set the position of the text
    window.draw(coordText);  // draw the text


    sf::Vector2f screenPos = _coordTranslation.translate(mathPos);
    _mousePoint.setPosition(screenPos.x - _mousePoint.getRadius(), screenPos.y - _mousePoint.getRadius());
    window.draw(_mousePoint);
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/
