#include "font.h"
#include "sidebar.h" // for class definition
#include "constants.h" // for SCREEN_HEIGHT
#include "polar.h"
#include <iostream> // for cout, cerr
using namespace std; // simplify std::cout to cout
#include <SFML/Graphics.hpp> // for sf::RenderWindow, sf::RectangleShape, sf::Text, sf::Color, sf::Vector2f, sf::CircleShape
#include "system.h"
#include "plot.h"

namespace
    {
    // Plot the equation once on a scratch copy of the graph state, so an
    // invalid equation (e.g. "logx") throws here, before it is added to the
    // history. Otherwise every redraw would throw again and the app would
    // hang in the error loop.
    void validate_equation(const string& equation, const GraphInfo& info)
        {
        GraphInfo scratch = info;
        scratch._history = {equation};
        scratch._colors = {sf::Color::Black};
        scratch._mode = equation.find("theta") != string::npos ? GraphInfo::POLAR : GraphInfo::CARTESIAN;

        streambuf* out = cout.rdbuf(nullptr);  // silence the engine trace
        try
            {
            Plot plot(&scratch);
            plot(scratch._domain.x, scratch._domain.y, 0.1f);
            }
        catch (...)
            {
            cout.rdbuf(out);
            throw;  // shown once by Animate::run; the input stays in the box
            }
        cout.rdbuf(out);
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

Sidebar::Sidebar(float left, float width) : _left(left), _width(width),
_rect(sf::Vector2f(width, SCREEN_HEIGHT)), _showCursor(true), _info(nullptr), _cursorPos(0)
    {
    _font = app_font();  // shared font, loaded once
    //  set the sidebar text
    _sb_text.setFont(_font);  // font for the sidebar text
    _sb_text.setCharacterSize(20);  // character size for the sidebar text
    _sb_text.setPosition(_left + 10, 10);  // position for the sidebar text
    _sb_text.setFillColor(sf::Color::Black);  // color for the sidebar text
    // set the sidebar rectangle
    _rect.setFillColor(sf::Color(255, 255, 255));  // color for the sidebar rectangle
    _rect.setPosition(_left, 0);  // position for the sidebar rectangle
    //set the input box
    _inputBox.setSize(sf::Vector2f(_width - 60, 30));  // size for the input box
    _inputBox.setPosition(_left + 40, 50);  // position for the input box
    _inputBox.setFillColor(sf::Color::White);  //  color for the input box
    _inputBox.setOutlineColor(sf::Color::Black);  // outline color for the input box
    _inputBox.setOutlineThickness(1);  // outline thickness for the input box
    // set  the input text
    _inputText.setFont(_font);  // font for the input text
    _inputText.setCharacterSize(20);  // character size for the input text
    _inputText.setFillColor(sf::Color::Black);  // color for the input text
    _inputText.setPosition(_left + 45, 55);  // position for the input text
    //  set the instruction label
    _instructionLabel.setFont(_font);  // font for the instruction label
    _instructionLabel.setCharacterSize(15);  // character size for the instruction label
    _instructionLabel.setFillColor(sf::Color::Black);  // color for the instruction label
    _instructionLabel.setString("INSTRUCTIONS:\nZoom In: ]\nZoom Out: [\nPan: Up Down Left Right Arrow Keys\nRose Curve Step: V F G D\nToggle Coordinates: Tab\nAdd Function: Enter\nDelete Function: Click Circle Button\nSelect Function: Click Function Box\n");
    _instructionLabel.setPosition(_left + 10, SCREEN_HEIGHT - 200);  // position for the instruction label

    updateText(); //  update the text
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Sidebar::draw(sf::RenderWindow& window)
    {
    window.draw(_rect); // draw the rectangle for the sidebar background
    window.draw(_sb_text); // draw the text for the sidebar

    window.draw(_inputBox); // draw the input box
    window.draw(_inputText); // draw the input text

    sf::RectangleShape addButton(sf::Vector2f(20, 20)); // add button
    addButton.setPosition(_left + 10, 55); // position of the add button
    addButton.setFillColor(sf::Color::Green); // color of the add button
    window.draw(addButton); // draw the add button

    _addButtonText.setFont(_font); // font for the add button text
    _addButtonText.setCharacterSize(20); // character size for the add button text
    _addButtonText.setFillColor(sf::Color::White); // color for the add button text
    _addButtonText.setString("+"); // string for the add button text
    _addButtonText.setPosition(_left + 14, 52); // position for the add button text
    window.draw(_addButtonText); // draw the add button text


    window.draw(_instructionLabel); // draw the instruction label


    if (_showCursor)  // if show cursor
        {
        sf::RectangleShape cursor(sf::Vector2f(2, 20));  // create a rectangle shape for the cursor
        cursor.setFillColor(sf::Color::Black);  // color of the cursor
        float cursorX = _inputText.findCharacterPos(_cursorPos).x;   // cursor position
        cursor.setPosition(cursorX, _inputText.getPosition().y + 5);  // position of the cursor
        window.draw(cursor);  // draw the cursor
        }


    float yPos = 100.0f;  // y position
    for (size_t i = 0; i < _functions.size(); ++i)  // for each function
        {

        sf::CircleShape deleteButton(10); // delete button
        deleteButton.setPosition(_left + 10, yPos + 5); // position of the delete button
        deleteButton.setFillColor(_colors[i]); // color of the delete button
        window.draw(deleteButton); // draw the delete button


        sf::RectangleShape functionBox(sf::Vector2f(_width - 60, 30));  // function box
        functionBox.setPosition(_left + 40, yPos);  // position of the function box
        functionBox.setFillColor(sf::Color::White);  // color of the function box
        functionBox.setOutlineColor(sf::Color::Black);  // outline color of the function box
        functionBox.setOutlineThickness(1);  // outline thickness of the function box
        window.draw(functionBox);  // draw the function box

        sf::Text functionText;  // text for the function
        functionText.setFont(_font);  // font for the function text
        functionText.setCharacterSize(20);  // character size for the function text
        functionText.setFillColor(sf::Color::Black);  // color for the function text
        functionText.setString((_info ? _info->getFunctionPrefix() : string()) + _functions[i]);  // string for the function text
        functionText.setPosition(_left + 45, yPos + 5);  // position for the function text
        window.draw(functionText);   // draw the function text

        yPos += 40.0f;  // increment y position


        }
    }

//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Sidebar::updateText()  // Update the text
    {
    _sb_text.setString("Input Functions:");
    }

void Sidebar::setFunctions(const vector<string>&functions, const vector<sf::Color>&colors) // Set the functions
    {
    _functions = functions;  // set the functions
    _colors = colors;  // set the colors
    updateText();  // update the text
    }

void Sidebar::removeFunction(size_t index, GraphInfo* info)  // Remove a function
    {
    if (index < _functions.size() && index < _colors.size())  // if index is valid
        {
        _functions.erase(_functions.begin() + index);  // erase the function
        _colors.erase(_colors.begin() + index);  // erase the color
        info->_history.erase(info->_history.begin() + index);  // erase the history
        info->_colors.erase(info->_colors.begin() + index);  // erase the colors
        updateText();  // update the text
        }
    else
        {
        cout << "Index out of range: " << index << endl;  // print index out of range
        cout << "Current _functions size: " << _functions.size() << ", _colors size: " << _colors.size() << endl;
        }
    }
void Sidebar::selectFunction(size_t index, GraphInfo* info)  // Select a function
    {
    if (index < _functions.size())
        {
        info->_currentFunctionIndex = index;  // set the current function index
        updateText();
        }
    else
        {
        cout << "Index out of range: " << index << endl;  // print index out of range
        }
    }

string Sidebar::getCurrentFunction(GraphInfo* info) const   // Get the current function
    {
    if (info->_currentFunctionIndex >= 0 && info->_currentFunctionIndex < _functions.size())  // if current function index is valid
        {
        return _functions[info->_currentFunctionIndex];
        }
    return "";
    }

sf::Color Sidebar::getCurrentFunctionColor(GraphInfo* info) const // Get the current function color
    {
    if (info->_currentFunctionIndex >= 0 && info->_currentFunctionIndex < _colors.size()) // If the current function index is valid
        {
        return _colors[info->_currentFunctionIndex]; // Return the color of the current function
        }
    return sf::Color::White; // Return white if the current function index is invalid
    }

/**----------------------------------------------
 * *                   INFO
 *  1.handle TextEntered event
 *  2.handle MouseButtonPressed event
 *  3.handle KeyPressed event
 *  4.handle cursor blinking
 *---------------------------------------------**/
void Sidebar::handleEvent(const sf::Event& event, GraphInfo* info)  // Handle events
    {
    _info = info;  // remembered for draw(), which has no GraphInfo parameter
    if (info->_mode != GraphInfo::INPUT)
        {
        if (info->_mode == GraphInfo::INPUT)
            {
            if (event.type == sf::Event::TextEntered)  // Text entered event
                {
                handleTextEntered(event, info);
                }
            }
        switch (event.type)
            {
                case sf::Event::TextEntered:  // Text entered event
                    handleTextEntered(event, info);
                    break;

                case sf::Event::MouseButtonPressed:  // Mouse button pressed event
                    handleMouseButtonPressed(event, info);
                    break;

                case sf::Event::KeyPressed:  // Key pressed event
                    handleKeyPressed(event, info);
                    break;

                default:
                    break;
            }

        handleCursorBlinking();  // Handle cursor blinking
        }

    }

void Sidebar::handleTextEntered(const sf::Event& event, GraphInfo* info)  // Handle text entered event
    {
    if (event.text.unicode == '\b')  // If the unicode is backspace
        {
        if (!_inputEquation.empty() && _cursorPos > 0)
            {
            _inputEquation.erase(_cursorPos - 1, 1);
            _cursorPos--;
            }
        }
    else if (event.text.unicode == '\n' || event.text.unicode == '\r')  // Enter: '\n' on macOS, '\r' on Linux/Windows
        {
        if (!_inputEquation.empty())
            {
            validate_equation(_inputEquation, *info);  // throws (and adds nothing) if invalid

            if (_inputEquation.find("theta") != string::npos)
                {
                info->_mode = GraphInfo::POLAR;
                }
            else
                {
                info->_mode = GraphInfo::CARTESIAN;
                }

            _functions.push_back(_inputEquation);  // Push back the input equation
            info->_history.push_back(_inputEquation);  // Push back the input equation to the history
            sf::Color color = info->generateDistinctColor();  // Generate a distinct color
            _colors.push_back(color);  // Push back the color
            info->_colors.push_back(color);  // Push back the color to the colors


            _inputEquation.clear();  // Clear the input equation
            _inputText.setString(_inputEquation);  // Set the input text
            _cursorPos = 0;  // Set the cursor position to 0
            updateText();  // Update the text
            }
        }
    else
        {
        _inputEquation.insert(_cursorPos, 1, static_cast<char>(event.text.unicode));  // Insert the text
        _cursorPos++;  // Increment the cursor position
        }
    _inputText.setString(_inputEquation);  // Set the input text
    }

void Sidebar::handleMouseButtonPressed(const sf::Event& event, GraphInfo* info)  // Handle mouse button pressed event
    {
    if (event.mouseButton.button == sf::Mouse::Left)  // If the mouse button is left
        {
        float yPos = 100.0f;
        for (size_t i = 0; i < _functions.size(); ++i)  // For each function
            {
            sf::FloatRect boxBounds(_left + 40, yPos, _width - 60, 30); // function box bounds
            sf::FloatRect deleteBounds(_left + 10, yPos + 5, 30, 30);  // delete button bounds

            if (deleteBounds.contains(event.mouseButton.x, event.mouseButton.y))
                {
                removeFunction(i, info); //delete button at index i clicked
                break;
                }
            else if (boxBounds.contains(event.mouseButton.x, event.mouseButton.y)) // function box clicked
                {
                selectFunction(i, info); // call select function
                break;
                }
            yPos += 40.0f;
            }

        sf::FloatRect addBounds(_left + 10, 55, 30, 30); // add button bounds
        if (addBounds.contains(event.mouseButton.x, event.mouseButton.y))  // add button clicked
            {
            if (!_inputEquation.empty())  // if input equation is not empty
                {
                validate_equation(_inputEquation, *info);  // throws (and adds nothing) if invalid
                _functions.push_back(_inputEquation);  // push back the input equation
                info->_history.push_back(_inputEquation);  // push back the input equation to the history
                sf::Color color = info->generateDistinctColor();  // generate a distinct color
                _colors.push_back(color);  // push back the color
                info->_colors.push_back(color);  // push back the color to the colors
                _inputEquation.clear();  // clear the input equation
                _inputText.setString(_inputEquation);  // set the input text
                _cursorPos = 0;  // set the cursor position to 0
                updateText();  // update the text
                }
            }

        }
    }

void Sidebar::handleKeyPressed(const sf::Event& event, GraphInfo* info)  // Handle key pressed event
    {
    switch (event.key.code)  // Switch on the key code
        {
            case sf::Keyboard::Left:  // Left arrow key
                if (_cursorPos > 0)  // If the cursor position is greater than 0
                    {
                    _cursorPos--;
                    }
                break;

            case sf::Keyboard::Right:
                if (_cursorPos < _inputEquation.length())       // Right arrow key
                    {
                    _cursorPos++;
                    }
                break;

            case sf::Keyboard::Tab:  // Tab key
                info->toggleMode();  // Toggle the mode
                updateText();
                break;

            default:
                break;
        }
    }

void Sidebar::handleCursorBlinking()  // Handle cursor blinking
    {
    if (_cursorClock.getElapsedTime().asSeconds() >= 0.5f)  // If the elapsed time is greater than 0.5 seconds
        {
        _showCursor = !_showCursor;  // Toggle the cursor
        _cursorClock.restart();  // Restart the clock
        }
    }