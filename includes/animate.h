#ifndef ANIMATE_H
#define ANIMATE_H

#include <SFML/Graphics.hpp>
#include "graphInfo.h"
#include "system.h"
#include "sidebar.h"

class Animate
    {
    public:
        Animate();
        void run(); // run main loop
        void processEvents(); // process the events
        void update(); // update the system state
        void render();  // render the graphics

    private:
        sf::RenderWindow _window; // main SFML window
        System _system; // container for all the animated objects
        bool _mouseIn; // if mouse is in the screen

        sf::CircleShape _mousePoint; // The little red dot
        sf::Font _font; // font to draw on main screen
        sf::Text _myTextLabel; // text to draw on main screen
        Sidebar _sidebar; // rectangular message sidebar
        GraphInfo _info;

        // helper function to convert mouse position to string
        string mouse_pos_string(sf::RenderWindow& window);

    };


#endif // ANIMATE_H
