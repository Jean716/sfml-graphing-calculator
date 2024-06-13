#ifndef ANIMATE_H
#define ANIMATE_H

#include <SFML/Graphics.hpp>
#include "graphInfo.h"
#include "system.h"
#include "sidebar.h"
#include "graph.h"
#include "polar.h"


// user inteactions
class Animate
    {
    public:
        Animate(); // default constructor
        void set_info(GraphInfo* info); // set the information of the graph
        void run(); // run main loop
        void processEvents(); // process the events
        void update(); // update the system state
        void render();  // render the graphics


    private:
        sf::RenderWindow _window; // main SFML window
        GraphInfo* _info; // graph information
        System _system; // container for all the animated objects
        Sidebar _sidebar; // rectangular message sidebar
        Graph _graph; // graph object
        int _command;

        bool _mouseIn; // if mouse is in the screen
        sf::CircleShape _mousePoint; // The little red dot
        sf::Font _font; // font to draw on main screen
        sf::Text _myTextLabel; // text to draw on main screen
        sf::Text _coordLabel; // math coordinates
        sf::Text _domainLabel;
        CoordTranslation  _coordTranslation;
        bool _isPolarMode = false;
        Polar _polar;
        sf::Vector2f _lastMousePos;

        // helper function to convert mouse position to string
        string mouse_pos_string(sf::RenderWindow& window);

        vector<string> _functions;
        bool _isDragging;
        sf::Vector2f _dragStartPos;

        // Helper methods to display domain and coordinates
        void drawCartesianDomainAndCoordinates(sf::RenderWindow& window);
        void drawPolarDomainAndCoordinates(sf::RenderWindow& window);


    };


#endif // ANIMATE_H