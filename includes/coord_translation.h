#ifndef COORD_TRANSLATION_H
#define COORD_TRANSLATION_H

#include <SFML/Graphics.hpp>
#include "graphInfo.h"


class CoordTranslation
    {
    public:
        CoordTranslation();
        CoordTranslation(GraphInfo* info);
        void set_info(GraphInfo* info); // set the information of the graph
        sf::Vector2f translate(const sf::Vector2f& point) const; // translate the math point to screen coord
        sf::Vector2f getMathCoords(const sf::Vector2f& point) const; // screen coord to math coord
        sf::Vector2f operator()(const sf::Vector2f& point) const; // operator overloading


    private:
        GraphInfo* _info;
    };

#endif 




