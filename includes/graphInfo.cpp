#include "graphInfo.h" //for class definition
#include <iostream> //for cout, cerr
#include <cassert> //for assert
using namespace std; // simplify std::cout to cout
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

// Default constructor
GraphInfo::GraphInfo()
    : _windowDimensions(SCREEN_WIDTH, SCREEN_HEIGHT),
    _origin(WORK_PANEL / 2, SCREEN_HEIGHT / 2), _domain(DEFAULT_DOMAIN),
    _scale(DEFAULT_SCALE), _points(DEFAULT_POINTS), _offsetX(DEFAULT_OFFSET_X),
    _offsetY(DEFAULT_OFFSET_Y), _mode(CARTESIAN)
    {
    }

//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void GraphInfo::zoom(float factor)
    {
    _scale *= factor;
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void GraphInfo::pan(float deltaX, float deltaY)
    {
    _offsetX += deltaX;
    _offsetY += deltaY;
    }

//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

sf::Color GraphInfo::generateDistinctColor()
    {
    return distinctColors[rand() % distinctColors.size()];
    }

//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void GraphInfo::evaluateMode(const string& equation)
    {
    if (equation.find("theta") != string::npos || equation.find("θ") != string::npos)
        {
        _mode = POLAR;
        }
    else
        {
        _mode = CARTESIAN;
        }
    }

//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void GraphInfo::toggleMode()
    {
    if (_mode == CARTESIAN)
        {
        _mode = POLAR;
        }
    else
        {
        _mode = CARTESIAN;
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

vector<vector<sf::Vector2f>> GraphInfo::getPointsData() const
    {
    return _pointsData;
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void GraphInfo::setPointsData(const vector<vector<sf::Vector2f>>& pointsData)
    {
    _pointsData = pointsData;
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

string GraphInfo::getFunctionPrefix() const
    {
    if (_mode == POLAR)
        {
        return "r = ";
        }
    else
        {
        return "y = ";
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void GraphInfo::panPolar(float dr)
    {
    _origin.x += dr * cos(_domain.x);
    _origin.y += dr * sin(_domain.x);
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void GraphInfo::adjustTheta(float dtheta)
    {
    _domain.x += dtheta;
    _domain.y += dtheta;
    }

