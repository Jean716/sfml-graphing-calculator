#ifndef SIDEBAR_H  // If not defined
#define SIDEBAR_H  // Define it

#include <SFML/Graphics.hpp> //for sf::RectangleShape, sf::Text
#include <iostream> //for cout, cerr
#include <string> //for string
#include <vector> //for vector
#include "graphInfo.h" //for class definition


class Sidebar
    {
    public:
        Sidebar(float left = SIDE_BAR_LEFT, float width = SIDE_BAR_WIDTH); // Constructor
        void draw(sf::RenderWindow& window); // Draw the sidebar

        void handleEvent(const sf::Event& event, GraphInfo* info); // Handle events
        void handleTextEntered(const sf::Event& event, GraphInfo* info);
        void handleMouseButtonPressed(const sf::Event& event, GraphInfo* info);
        void handleKeyPressed(const sf::Event& event, GraphInfo* info);
        void handleCursorBlinking();

        void setFunctions(const vector<string>& functions, const vector<sf::Color>& colors); // Set the functions
        void removeFunction(size_t index, GraphInfo* info); // Remove a function
        void selectFunction(size_t index, GraphInfo* info);
        string getCurrentFunction(GraphInfo* info) const; // Get the current function
        sf::Color getCurrentFunctionColor(GraphInfo* info) const; // Get the current function color
        bool isInputEmpty() const { return _inputEquation.empty(); } // True when nothing is being typed


    private:
        string _inputEquation;    // Equation input by the user
        sf::Font _font;       // Font for the text
        sf::Text _sb_text;   // Text for the sidebar
        sf::RectangleShape _rect;  // Rectangle for the sidebar background
        vector<string> _functions; // List of functions
        float _left; // Left position of the sidebar
        float _width; // Width of the sidebar
        sf::RectangleShape _inputBox; // Input box for the equation
        sf::Text _inputText; // Text for the input box
        sf::Text _instructionLabel; // Instruction label
        sf::Text _addButtonText; // Add button text
        bool _showCursor; // Show cursor for input box
        sf::Clock _cursorClock; // Clock for cursor blinking
        vector<sf::Color> _colors; // Colors for the functions
        GraphInfo* _info; // Pointer to the graph info
        int _cursorPos; // Cursor position in the input box
        sf::Text _errorLabel; // Error label



        void updateText(); // Update the text for the input box
    };

#endif // SIDEBAR_H