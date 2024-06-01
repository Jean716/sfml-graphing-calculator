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
        Sidebar();
        Sidebar(float left, float width);

        void draw(sf::RenderWindow& window);
        void handleEvent(const sf::Event& event);

        string& operator [](int index);
        string getInput() const;


    private:
        sf::RectangleShape _rect;            //sidebar rectangle
        vector<string> _items;               //strings to place on the sidebar
        sf::Font _font;                      //used to draw text
        sf::Text _sb_text;
        //used to draw strings on the window object
        float _left;
        float _width;

        sf::RectangleShape _inputBox;
        sf::Text _inputText;
        string _inputString;

    };

#endif // SIDEBAR_H
