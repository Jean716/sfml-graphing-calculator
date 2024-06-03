#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// this class is used to create a sidebar on the window object
// user can input the strings to be displayed on the sidebar
// display the coordinates of the mouse on the sidebar
class Sidebar
    {
    public:

        Sidebar(float left = 1120, float width = 280); // constructor with default values

        void draw(sf::RenderWindow& window);
        string& operator [](int index); // get the string at the index
        void handleEvent(const sf::Event& event); // handle the events
        string getInput() const; // get the input string from user



    private:
        vector<string> _items;               //strings to place on the sidebar
        sf::RectangleShape _rect;            //sidebar rectangle
        sf::Font _font;                      //used to draw text
        sf::Text _sb_text;
        //used to draw strings on the window object
        float _left;
        float _width;

        sf::RectangleShape _inputBox; // input box
        sf::Text _inputText; // text in the input box
        string _inputString; // to store the input string
        bool _isFocused; // if the input box is focused
        bool _showCursor; // cursor blink flag
        sf::Clock _cursorClock; // cursor blink clock

    };

#endif // SIDEBAR_H