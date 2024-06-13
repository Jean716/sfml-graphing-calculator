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
    _offsetY(DEFAULT_OFFSET_Y), _mode(CARTESIAN), a(1.0f), b(1.0f), _currentFunctionIndex(-1), _history(0), _colors(0)
    {
    a = 5.0f;
    b = 6.0f;
    }


//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void GraphInfo::zoom(float factor)  // Zoom the graph
    {
    _scale *= factor;
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void GraphInfo::pan(float deltaX, float deltaY)  // Pan the graph
    {
    _offsetX += deltaX;
    _offsetY += deltaY;
    }

//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

sf::Color GraphInfo::generateDistinctColor()  // Generate a distinct color
    {
    return distinctColors[rand() % distinctColors.size()];
    }

//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void GraphInfo::evaluateMode(const string& equation)  // Evaluate the mode of the graph
    {
    if (equation.find("theta") != string::npos || equation.find("θ") != string::npos)  // If the equation contains theta
        {
        _mode = POLAR;
        }
    else
        {
        _mode = CARTESIAN;
        }
    }

//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void GraphInfo::toggleMode()  // Toggle the mode of the graph
    {
    if (_mode == CARTESIAN) // If the mode is cartesian
        {
        _mode = POLAR;  // Set the mode to polar
        }
    else
        {
        _mode = CARTESIAN;  // Set the mode to cartesian
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

vector<vector<sf::Vector2f>> GraphInfo::getPointsData() const  // Get the points data
    {
    return _pointsData;  // Return the points data
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void GraphInfo::setPointsData(const vector<vector<sf::Vector2f>>& pointsData)  // Set the points data
    {
    _pointsData = pointsData;  // Set the points data
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

string GraphInfo::getFunctionPrefix() const  // Get the function prefix
    {
    if (_mode == POLAR)  // If the mode is polar
        {
        return "r = ";  // Return r =
        }
    else
        {
        return "y = ";  // Return y =
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void GraphInfo::panPolar(float dr)  // Pan the graph in polar mode
    {
    _origin.x += dr * cos(_domain.x);  // Pan the graph in x direction
    _origin.y += dr * sin(_domain.x);  // Pan the graph in y direction
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void GraphInfo::adjustTheta(float dtheta)  // Adjust the theta
    {
    _domain.x += dtheta;  // Adjust the theta
    _domain.y += dtheta;  // Adjust the theta
    }
void GraphInfo::adjustA(float step) // Adjust the a
    {
    a += step; // a plus equal to step
    }

void GraphInfo::adjustB(float step) // Adjust the b
    {
    b += step; // b plus equal to step
    }

