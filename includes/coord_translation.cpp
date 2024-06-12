#include "coord_translation.h" // include the header file
#include <cassert> // include the assert library
/**=======================================================================================================================
 *                                                     COMMENT BLOCK
 *  Implemention of the conversion of screen coordinates and mathematical coordinates
 *  Implemention of the conversion of polar coordinates and cartesian coordinates
 *=======================================================================================================================**/
 /*======================================================= Constructor =======================================================*/
CoordTranslation::CoordTranslation() : _info(nullptr) {} // default constructor
CoordTranslation::CoordTranslation(GraphInfo* info) : _info(info) {} // parameterized constructor
/*======================================================= DIVISION =======================================================*/
// set the information of the graph
void CoordTranslation::set_info(GraphInfo* info)
    {
    _info = info; // set the information of the graph
    }
/*======================================================= DIVISION =======================================================*/
// covert math coord to screen coord
// screenX = originX + (mathX * scale) + offsetX
// screenY = originY - (mathY * scale) + offsetY
sf::Vector2f CoordTranslation::translate(const sf::Vector2f& mathPoint) const
    {
    assert(_info != nullptr && "GraphInfo pointer is null!"); // check if the pointer is null
    float screenX = _info->getOrigin().x + (mathPoint.x * _info->getScale()) + _info->getOffsetX();
    float screenY = _info->getOrigin().y - (mathPoint.y * _info->getScale()) + _info->getOffsetY();
    return sf::Vector2f(screenX, screenY);  // return the screen coord
    }
/*======================================================= DIVISION =======================================================*/
// operator overloading
sf::Vector2f CoordTranslation::operator()(const sf::Vector2f& mathPoint) const
    {
    return translate(mathPoint); // call the translate function and return the screen coord
    }
/*======================================================= DIVISION =======================================================*/
// convert screen coord to math coord
// mathX = (screenX - originX - offsetX) / scale
// mathY = (originY - screenY - offsetY) / scale
sf::Vector2f CoordTranslation::getMathCoords(const sf::Vector2f& screenPoint) const
    {
    assert(_info != nullptr && "GraphInfo pointer is null!"); // check if the pointer is null
    float x = (screenPoint.x - _info->getOrigin().x - _info->getOffsetX()) / _info->getScale();
    float y = (_info->getOrigin().y - screenPoint.y - _info->getOffsetY()) / _info->getScale();
    return sf::Vector2f(x, y); // return the math coord
    }
/*======================================================= DIVISION =======================================================*/
// convert polar to cartesian
// x = r * cos(theta)
// y = r * sin(theta)
sf::Vector2f CoordTranslation::polarToCartesian(float r, float theta) const
    {
    float x = r * cos(theta);
    float y = r * sin(theta);
    return sf::Vector2f(x, y); // return the cartesian coord
    }
/*======================================================= DIVISION =======================================================*/
// convert cartesian to polar
// r = sqrt(x^2 + y^2)
 // theta = arctan(y/x)
sf::Vector2f CoordTranslation::cartesianToPolar(const sf::Vector2f point) const
    {
    float r = sqrt(pow(point.x, 2) + pow(point.y, 2));
    float theta = atan2(point.y, point.x);
    return sf::Vector2f(r, theta); // return the polar coord
    }

