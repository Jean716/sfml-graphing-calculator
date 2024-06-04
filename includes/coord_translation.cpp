#include "coord_translation.h"
#include <cassert>

CoordTranslation::CoordTranslation() : _info(nullptr) {}
CoordTranslation::CoordTranslation(GraphInfo* info) : _info(info) {}

// covert math coord to screen coord
sf::Vector2f CoordTranslation::translate(const sf::Vector2f& point) const
    {
    assert(_info != nullptr && "GraphInfo pointer is null!");
    float screenX = _info->getOrigin().x + point.x * _info->getScale();
    float screenY = _info->getOrigin().y - point.y * _info->getScale();
    return sf::Vector2f(screenX, screenY);
    }

//convert screen coord to math coord 
sf::Vector2f CoordTranslation::getMathCoords(const sf::Vector2f& point) const
    {
    assert(_info != nullptr && "GraphInfo pointer is null!");
    float x = (point.x - _info->getOrigin().x) / _info->getScale();
    float y = (_info->getOrigin().y - point.y) / _info->getScale();
    return sf::Vector2f(x, y);
    }

sf::Vector2f CoordTranslation::operator()(const sf::Vector2f& point) const
    {
    return translate(point);
    }

void CoordTranslation::set_info(GraphInfo* info)
    {
    _info = info;
    }

