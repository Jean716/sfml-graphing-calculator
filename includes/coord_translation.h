#ifndef COORD_TRANSLATION_H
#define COORD_TRANSLATION_H

#include <SFML/Graphics.hpp>
#include "graphInfo.h"


class CoordTranslation
    {
    public:
        CoordTranslation(GraphInfo* info);
        sf::Vector2f translate(const sf::Vector2f& point) const; // translate the point to screen coord
        sf::Vector2f operator()(const sf::Vector2f& point) const; // operator overloading to translate the point to screen coord
        // simplify the code

    private:
        GraphInfo* _info;
    };

#endif 


// /*

// GraphInfo info;
// info._scale = 56.0f;
// info._origin = sf::Vector2f(560, 400);

// CoordTranslation coordTranslation(&info);
// sf::Vector2f mathPoint(1.0f, 2.0f);
// sf::Vector2f screenPoint = coordTranslation(mathPoint); // 使用运算符重载



// */


