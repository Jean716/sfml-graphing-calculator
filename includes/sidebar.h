#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "graphInfo.h"

class Sidebar
    {
    public:
        Sidebar(float left = SIDE_BAR_LEFT, float width = SIDE_BAR_WIDTH);
        void draw(sf::RenderWindow& window);
        void handleEvent(const sf::Event& event, GraphInfo* info);
        void setFunctions(const vector<string>& functions, const vector<sf::Color>& colors);

    private:
        string _inputEquation;
        sf::Font _font;
        sf::Text _sb_text;
        sf::RectangleShape _rect;
        vector<string> _functions;

        float _left;
        float _width;

        sf::RectangleShape _inputBox;
        sf::Text _inputText;
        bool _showCursor;
        sf::Clock _cursorClock;
        vector<sf::Color> _colors;
        int _cursorPos;

        void updateText();
        void removeFunction(size_t index, GraphInfo* info);
    };

#endif // SIDEBAR_H