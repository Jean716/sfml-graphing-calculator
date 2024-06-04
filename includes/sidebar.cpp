#include "sidebar.h"
#include "constants.h"

Sidebar::Sidebar(float left, float width) : _left(left), _width(width), _rect(sf::Vector2f(width, SCREEN_HEIGHT))
    {
    // load the font
    if (!_font.loadFromFile("arial.ttf"))
        {
        // Handle error
        }


    _sb_text.setFont(_font);
    _sb_text.setCharacterSize(20);
    _sb_text.setPosition(_left + 10, 10);
    _sb_text.setFillColor(sf::Color::Black);

    _rect.setFillColor(sf::Color(236, 236, 236));
    _rect.setPosition(_left, 0);

    }


void Sidebar::draw(sf::RenderWindow& window)
    {
    window.draw(_rect);
    window.draw(_sb_text);

    // draw the history
    float yOffset = 50.0f;
    for (const auto& expr : _history)
        {
        sf::Text historyText(expr, _font, 20);
        historyText.setFillColor(sf::Color::White);
        historyText.setPosition(_left + 10, yOffset);
        window.draw(historyText);
        yOffset += 30.0f; // increment the y offset
        }
    }



string& Sidebar::operator [](int index)
    {
    return _history[index];
    }


void Sidebar::handleEvent(const sf::Event & event)
    {
    if (event.type == sf::Event::TextEntered)
        {
        if (event.text.unicode == '\b')
            {
            if (!_inputEquation.empty())
                {
                _inputEquation.pop_back();
                }
            }
        else if (event.text.unicode == '\r')
            {
            // press enter to submit the equation
            _history.push_back(_inputEquation);
            _inputEquation.clear();
            }
        else
            {
            _inputEquation += static_cast<char>(event.text.unicode);
            }
        updateText();
        }
    }



string Sidebar::getInput() const
    {
    return _inputEquation;
    }

void Sidebar::updateText()
    {
    _sb_text.setString("Input: " + _inputEquation);
    }