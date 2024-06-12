#ifndef COORD_TRANSLATION_H
#define COORD_TRANSLATION_H

#include <SFML/Graphics.hpp>
#include "graphInfo.h"


class CoordTranslation
    {
    public:
        CoordTranslation(); //  default constructor
        CoordTranslation(GraphInfo* info);  // parameterized constructor

        void set_info(GraphInfo* info); // set the information of the graph

        sf::Vector2f translate(const sf::Vector2f& mathPoint) const; // translate the math point to screen coord
        sf::Vector2f operator()(const sf::Vector2f& mathPoint) const; // operator overloading
        sf::Vector2f getMathCoords(const sf::Vector2f& screenPoint) const; // screen coord to math coord


        sf::Vector2f polarToCartesian(float r, float theta) const; // translate polar to cartesian
        sf::Vector2f cartesianToPolar(const sf::Vector2f point) const; // translate cartesian to polar


    private:
        GraphInfo* _info;   // member variable 
    };

#endif 




