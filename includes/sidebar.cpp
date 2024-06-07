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
    _sb_text.setFillColor(sf::Color::Blue);

    _rect.setFillColor(sf::Color(236, 236, 236));
    _rect.setPosition(_left, 0);

    }


void Sidebar::draw(sf::RenderWindow& window)
    {
    window.draw(_rect);
    window.draw(_sb_text);

    // Draw the function list
    float yPos = 50.0f; // starting y position for function texts
    for (size_t i = 0; i < _functions.size(); ++i)
        {
        sf::Text functionText;
        functionText.setFont(_font);
        functionText.setCharacterSize(20);
        functionText.setFillColor(sf::Color::Blue);
        functionText.setString(std::to_string(i + 1) + ": " + _functions[i]);
        functionText.setPosition(_left + 10, yPos);
        window.draw(functionText);
        yPos += 30.0f; // increment y position for next text
        }
    }


// string& Sidebar::operator [](int index)
//     {
//     return _history[index];
//     }


void Sidebar::handleEvent(const sf::Event & event, GraphInfo* info)
    {
    if (event.type == sf::Event::KeyPressed)
        {
        // Check if the pressed key is a number key
        if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num9)
            {
            int index = event.key.code - sf::Keyboard::Num1;
            if (index < _functions.size())
                {
                info->setEquation(_functions[index]);
                updateText();
                }
            }
        }
    }


void Sidebar::updateText()
    {
    _sb_text.setString("Functions:");
    }

void Sidebar::setFunctions(const vector<string>& functions)
    {
    _functions = functions;
    updateText();
    }