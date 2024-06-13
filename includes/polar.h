#ifndef POLAR_H
#define POLAR_H

#include <SFML/Graphics.hpp>
#include "graphInfo.h"
#include "coord_translation.h"



class Polar
    {
    public:
        Polar();
        void draw(sf::RenderWindow& window, GraphInfo* info); // draw the polar graph
        void set_info(GraphInfo* info);  // set the information of the graph
        void drawPolarGrid(sf::RenderWindow& window, GraphInfo* info);  // draw the polar grid
        void drawPolarLabels(sf::RenderWindow& window, GraphInfo* info);  // draw the polar labels
        void drawPoints(sf::RenderWindow& window, GraphInfo* info);  // draw the points of the polar graph
        void drawRoseCurve(sf::RenderWindow& window, GraphInfo* info);  // draw the rose curve

    private:
        GraphInfo* _info;
        CoordTranslation _coordTranslation; // Coordinate translation object



    };

#endif // POLAR_COORDINATE_SYSTEM_H