#include "sidebar.h"
#include "constants.h"

Sidebar::Sidebar(float left, float width) : _left(left), _width(width), _isFocused(false), _showCursor(true)
    {
    _rect.setSize(sf::Vector2f(_width, 800));
    _rect.setFillColor(sf::Color(236, 236, 236));
    _rect.setPosition(_left, 0);

    if (!_font.loadFromFile("arial.ttf"))
        {
        // Handle error
        }
    _sb_text.setFont(_font);
    _sb_text.setFillColor(sf::Color::Black);
    _sb_text.setCharacterSize(20);

    // add the default items
    _items.push_back("Enter an equation:");

    // initialize the input box
    _inputBox.setSize(sf::Vector2f(_width - 20, 30));
    _inputBox.setFillColor(sf::Color(255, 255, 255));
    _inputBox.setOutlineColor(sf::Color::Black);
    _inputBox.setOutlineThickness(1);
    _inputBox.setPosition(_left + 10, 50);

    _inputText.setFont(_font);
    _inputText.setFillColor(sf::Color::White);
    _inputText.setCharacterSize(20);
    _inputText.setPosition(_left + 15, 55);

    }



void Sidebar::draw(sf::RenderWindow& window)
    {
    const float VERTICAL_LINE_SPACING = 5.0;//  5 pixels between lines
    const float LEFT_MARGIN = 10.0;  //  10 pixels from left edge

    window.draw(_rect); //draw the rectangle of the sidebar
    float height = 10; //start 10 pixels from the top

    for (const auto& item : _items)
        {
        if (item.empty())
            {
            continue; // skip empty strings
            }
        _sb_text.setString(item); // set the text
        _sb_text.setPosition(sf::Vector2f(_left + LEFT_MARGIN, height)); // set the position
        height += _sb_text.getLocalBounds().height + VERTICAL_LINE_SPACING; // update the height
        window.draw(_sb_text); // draw the text

        // drwa the input box and text
        window.draw(_inputBox);
        _inputText.setString(_inputString + (_showCursor ? "|" : "")); // display the cursor
        window.draw(_inputText);


        // display the cuosor state
        if (_cursorClock.getElapsedTime().asSeconds() >= 0.5f)
            {
            _showCursor = !_showCursor;
            _cursorClock.restart();
            }
        }
    }



string& Sidebar::operator [](int index)
    {
    return _items[index];
    }


void Sidebar::handleEvent(const sf::Event & event)
    {
    // handle mouse click
    if (event.type == sf::Event::MouseButtonPressed)
        {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (_inputBox.getGlobalBounds().contains(mousePos))
            {
            _isFocused = true;
            }
        else
            {
            _isFocused = false;
            }
        }



    // hanlde text input
    if (_isFocused && event.type == sf::Event::TextEntered)
        {
        if (event.text.unicode == '\b')// handle backspace
            {
            if (!_inputString.empty())
                {
                _inputString.pop_back();
                }
            }
        else if (event.text.unicode < 128 && event.text.unicode >= 32)
            {
            _inputString += static_cast<char>(event.text.unicode);
            }
        }
    _inputText.setString(_inputString);
    }



string Sidebar::getInput() const
    {
    return _inputString;
    }