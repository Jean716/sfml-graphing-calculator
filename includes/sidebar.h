#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "graphInfo.h"
using namespace std;

// this class is used to create a sidebar on the window object
// user can input the strings to be displayed on the sidebar
// display the coordinates of the mouse on the sidebar
class Sidebar
    {
    public:

        Sidebar(float left = SIDE_BAR_LEFT, float width = SIDE_BAR_WIDTH);

        void draw(sf::RenderWindow& window);
        string& operator [](int index); // get the string at the index
        void handleEvent(const sf::Event& event); // handle the events
        string getInput() const; // get the input string from user



    private:


        string _inputEquation; // to store the input string
        sf::Font _font;                      //used to draw text
        sf::Text _sb_text;
        sf::RectangleShape _rect;            //sidebar rectangle
        vector<string> _history;              //store the strings to be displayed on the sidebar

        //used to draw strings on the window object
        float _left;
        float _width;

        void updateText(); // update the text on the sidebar


    };

#endif // SIDEBAR_H


// sf::RectangleShape _inputBox; // input box
   // sf::Text _inputText; // text in the input box
   // bool _isFocused; // if the input box is focused
   // bool _showCursor; // cursor blink flag
   // sf::Clock _cursorClock; // cursor blink clock
