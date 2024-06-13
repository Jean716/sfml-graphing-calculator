#include "sidebar.h" // for class definition
#include "constants.h" // for SCREEN_HEIGHT
#include "polar.h"
#include <iostream> // for cout, cerr
using namespace std; // simplify std::cout to cout
#include <SFML/Graphics.hpp> // for sf::RenderWindow, sf::RectangleShape, sf::Text, sf::Color, sf::Vector2f, sf::CircleShape
#include "system.h"
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

Sidebar::Sidebar(float left, float width) : _left(left), _width(width),
_rect(sf::Vector2f(width, SCREEN_HEIGHT)), _showCursor(true), _cursorPos(0)
    {
    if (!_font.loadFromFile("arial.ttf"))
        {
        cerr << "Error loading font." << endl;
        }

    _sb_text.setFont(_font);
    _sb_text.setCharacterSize(20);
    _sb_text.setPosition(_left + 10, 10);
    _sb_text.setFillColor(sf::Color::Black);

    _rect.setFillColor(sf::Color(255, 255, 255));
    _rect.setPosition(_left, 0);

    _inputBox.setSize(sf::Vector2f(_width - 60, 30));
    _inputBox.setPosition(_left + 40, 50);
    _inputBox.setFillColor(sf::Color::White);
    _inputBox.setOutlineColor(sf::Color::Black);
    _inputBox.setOutlineThickness(1);

    _inputText.setFont(_font);
    _inputText.setCharacterSize(20);
    _inputText.setFillColor(sf::Color::Black);
    _inputText.setPosition(_left + 45, 55);

    _instructionLabel.setFont(_font);
    _instructionLabel.setCharacterSize(15);
    _instructionLabel.setFillColor(sf::Color::Black);
    _instructionLabel.setString("INSTRUCTIONS:\nZoom In: [\nZoom Out: ]\nPan: Up Down Left Right Arrow Keys\nRose Curve Step: A D W E\nToggle Coordinates: Tab\nAdd Function: Enter\nDelete Function: Click Circle Button\nSelect Function: Click Function Box\n");
    _instructionLabel.setPosition(_left + 10, SCREEN_HEIGHT - 200);

    updateText();
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Sidebar::draw(sf::RenderWindow& window)
    {
    window.draw(_rect);
    window.draw(_sb_text);

    window.draw(_inputBox);
    window.draw(_inputText);

    sf::RectangleShape addButton(sf::Vector2f(20, 20));
    addButton.setPosition(_left + 10, 55);
    addButton.setFillColor(sf::Color::Green);
    window.draw(addButton);
    _addButtonText.setFont(_font);
    _addButtonText.setCharacterSize(20);
    _addButtonText.setFillColor(sf::Color::White);
    _addButtonText.setString("+");
    _addButtonText.setPosition(_left + 14, 52);
    window.draw(_addButtonText);


    window.draw(_instructionLabel);


    if (_showCursor)
        {
        sf::RectangleShape cursor(sf::Vector2f(2, 20));
        cursor.setFillColor(sf::Color::Black);
        float cursorX = _inputText.findCharacterPos(_cursorPos).x;
        cursor.setPosition(cursorX, _inputText.getPosition().y + 5);
        window.draw(cursor);
        }


    float yPos = 100.0f;
    for (size_t i = 0; i < _functions.size(); ++i)
        {

        sf::CircleShape deleteButton(10);
        deleteButton.setPosition(_left + 10, yPos + 5);
        deleteButton.setFillColor(_colors[i]);
        window.draw(deleteButton);


        sf::RectangleShape functionBox(sf::Vector2f(_width - 60, 30));
        functionBox.setPosition(_left + 40, yPos);
        functionBox.setFillColor(sf::Color::White);
        functionBox.setOutlineColor(sf::Color::Black);
        functionBox.setOutlineThickness(1);
        window.draw(functionBox);

        sf::Text functionText;
        functionText.setFont(_font);
        functionText.setCharacterSize(20);
        functionText.setFillColor(sf::Color::Black);
        functionText.setString(_info->getFunctionPrefix() + _functions[i]);
        functionText.setPosition(_left + 45, yPos + 5);
        window.draw(functionText);

        yPos += 40.0f;



        }
    }




void Sidebar::updateText()
    {
    _sb_text.setString("Input Functions:");
    }

void Sidebar::setFunctions(const vector<string>&functions, const vector<sf::Color>&colors)
    {
    _functions = functions;
    _colors = colors;
    updateText();
    }

void Sidebar::removeFunction(size_t index, GraphInfo* info)
    {
    if (index < _functions.size() && index < _colors.size())
        {
        _functions.erase(_functions.begin() + index);
        _colors.erase(_colors.begin() + index);
        info->_history.erase(info->_history.begin() + index);
        info->_colors.erase(info->_colors.begin() + index);
        updateText();
        }
    else
        {
        cout << "Index out of range: " << index << endl;
        cout << "Current _functions size: " << _functions.size() << ", _colors size: " << _colors.size() << endl;
        }
    }
void Sidebar::selectFunction(size_t index, GraphInfo* info)
    {
    if (index < _functions.size())
        {
        info->_currentFunctionIndex = index;
        updateText();
        }
    else
        {
        cout << "Index out of range: " << index << endl;
        }
    }

string Sidebar::getCurrentFunction(GraphInfo* info) const
    {
    if (info->_currentFunctionIndex >= 0 && info->_currentFunctionIndex < _functions.size())
        {
        return _functions[info->_currentFunctionIndex];
        }
    return "";
    }

sf::Color Sidebar::getCurrentFunctionColor(GraphInfo* info) const
    {
    if (info->_currentFunctionIndex >= 0 && info->_currentFunctionIndex < _colors.size())
        {
        return _colors[info->_currentFunctionIndex];
        }
    return sf::Color::White;
    }

/**----------------------------------------------
 * *                   INFO
 *  1.handle TextEntered event
 *  2.handle MouseButtonPressed event
 *  3.handle KeyPressed event
 *  4.handle cursor blinking
 *---------------------------------------------**/
void Sidebar::handleEvent(const sf::Event& event, GraphInfo* info)
    {
    if (info->_mode != GraphInfo::INPUT)
        {
        switch (event.type)
            {
                case sf::Event::TextEntered:
                    handleTextEntered(event, info);
                    break;

                case sf::Event::MouseButtonPressed:
                    handleMouseButtonPressed(event, info);
                    break;

                case sf::Event::KeyPressed:
                    handleKeyPressed(event, info);
                    break;

                default:
                    break;
            }

        handleCursorBlinking();
        }
    else
        {
        std::cout << "Current mode is INPUT" << std::endl;
        }
    }

void Sidebar::handleTextEntered(const sf::Event& event, GraphInfo* info)
    {
    if (event.text.unicode == '\b')
        {
        if (!_inputEquation.empty() && _cursorPos > 0)
            {
            _inputEquation.erase(_cursorPos - 1, 1);
            _cursorPos--;
            }
        }
    else if (event.text.unicode == '\n')
        {
        if (!_inputEquation.empty())
            {
            if (_inputEquation.find("theta") != std::string::npos)
                {
                info->_mode = GraphInfo::POLAR;
                }
            else
                {
                info->_mode = GraphInfo::CARTESIAN;
                }

            _functions.push_back(_inputEquation);
            info->_history.push_back(_inputEquation);
            sf::Color color = info->generateDistinctColor();
            _colors.push_back(color);
            info->_colors.push_back(color);


            _inputEquation.clear();
            _inputText.setString(_inputEquation);
            _cursorPos = 0;
            updateText();
            }
        }
    else
        {
        _inputEquation.insert(_cursorPos, 1, static_cast<char>(event.text.unicode));
        _cursorPos++;
        }
    _inputText.setString(_inputEquation);
    }

void Sidebar::handleMouseButtonPressed(const sf::Event& event, GraphInfo* info)
    {
    if (event.mouseButton.button == sf::Mouse::Left)
        {
        float yPos = 100.0f;
        for (size_t i = 0; i < _functions.size(); ++i)
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
        if (addBounds.contains(event.mouseButton.x, event.mouseButton.y))
            {
            if (!_inputEquation.empty())
                {
                _functions.push_back(_inputEquation);
                info->_history.push_back(_inputEquation);
                sf::Color color = info->generateDistinctColor();
                _colors.push_back(color);
                info->_colors.push_back(color);
                _inputEquation.clear();
                _inputText.setString(_inputEquation);
                _cursorPos = 0;
                updateText();
                }
            }
        }
    }

void Sidebar::handleKeyPressed(const sf::Event& event, GraphInfo* info)
    {
    switch (event.key.code)
        {
            case sf::Keyboard::Left:
                if (_cursorPos > 0)
                    {
                    _cursorPos--;
                    }
                break;

            case sf::Keyboard::Right:
                if (_cursorPos < _inputEquation.length())
                    {
                    _cursorPos++;
                    }
                break;

            case sf::Keyboard::Tab:
                info->toggleMode();
                updateText();
                break;

            default:
                break;
        }
    }

void Sidebar::handleCursorBlinking()
    {
    if (_cursorClock.getElapsedTime().asSeconds() >= 0.5f)
        {
        _showCursor = !_showCursor;
        _cursorClock.restart();
        }
    }