#include "coord_translation.h"

CoordTranslation::CoordTranslation(GraphInfo* info) : _info(info) {}

sf::Vector2f CoordTranslation::translate(const sf::Vector2f& point) const
    {
    // covert math coord to screen coord
    float screenX = point.x * _info->getScale() + _info->getOrigin().x;
    float screenY = -point.y * _info->getScale() + _info->getOrigin().y;
    return sf::Vector2f(screenX, screenY);
    }

sf::Vector2f CoordTranslation::operator()(const sf::Vector2f& point) const
    {
    return translate(point);
    }
