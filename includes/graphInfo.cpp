#include "graphInfo.h"
#include <iostream>

using namespace std;

// Default constructor
GraphInfo::GraphInfo()
    : _windowDimensions(SCREEN_WIDTH, SCREEN_HEIGHT),
    _origin(WORK_PANEL / 2, SCREEN_HEIGHT / 2), _domain(DEFAULT_DOMAIN),
    _scale(DEFAULT_SCALE), _points(DEFAULT_POINTS), _offsetX(DEFAULT_OFFSET_X),
    _offsetY(DEFAULT_OFFSET_Y), _mode(CARTESIAN)
    {
    }

// Getter and Setter methods
vector<string> GraphInfo::getEquations() const
    {
    return _equations;
    }

vector<sf::Color> GraphInfo::getColors() const
    {
    return _colors;
    }

void GraphInfo::addEquation(const string& equation)
    {
    _equations.push_back(equation);
    _colors.push_back(generateDistinctColor());
    evaluateMode(equation);
    }

void GraphInfo::setEquation(const string& equation)
    {
    cout << "Setting equation: " << equation << endl;
    _equations.clear();
    _equations.push_back(equation);
    }

void GraphInfo::removeEquation(size_t index)
    {
    if (index < _equations.size())
        {
        cout << "Removing equation at index: " << index << endl;
        cout << "Before removing, _equations size: " << _equations.size() << ", _colors size: " << _colors.size() << endl;

        _equations.erase(_equations.begin() + index);
        _colors.erase(_colors.begin() + index);

        cout << "After removing, _equations size: " << _equations.size() << ", _colors size: " << _colors.size() << endl;
        cout << "Equation removed successfully." << endl;
        }
    else
        {
        cout << "Index out of range: " << index << endl;
        }
    }

sf::Vector2f GraphInfo::getDomain() const
    {
    return _domain;
    }

void GraphInfo::setDomain(const sf::Vector2f& domain)
    {
    _domain = domain;
    }

sf::Vector2f GraphInfo::getOrigin() const
    {
    return _origin;
    }

void GraphInfo::setOrigin(const sf::Vector2f& origin)
    {
    _origin = origin;
    }

float GraphInfo::getScale() const
    {
    return _scale;
    }

void GraphInfo::setScale(float scale)
    {
    _scale = scale;
    }

float GraphInfo::getPoints() const
    {
    return _points;
    }

void GraphInfo::setPoints(int points)
    {
    _points = points;
    }

float GraphInfo::getOffsetX() const
    {
    return _offsetX;
    }

void GraphInfo::setOffsetX(float offsetX)
    {
    _offsetX = offsetX;
    }

float GraphInfo::getOffsetY() const
    {
    return _offsetY;
    }

void GraphInfo::setOffsetY(float offsetY)
    {
    _offsetY = offsetY;
    }

vector<sf::Vertex> GraphInfo::getVertices() const
    {
    return _vertices;
    }

void GraphInfo::setVertices(const vector<sf::Vertex>& vertices)
    {
    _vertices = vertices;
    }

void GraphInfo::zoom(float factor)
    {
    if (_mode == CARTESIAN || _mode == POLAR)
        {
        _scale *= factor;
        cout << "Zoom: new scale = " << _scale << endl;
        }
    }

void GraphInfo::pan(float deltaX, float deltaY)
    {
    _offsetX += deltaX;
    _offsetY += deltaY;
    cout << "Pan: new offset = (" << _offsetX << ", " << _offsetY << ")" << endl;
    }

void GraphInfo::setColor(const sf::Color& color)
    {
    _colors.clear();
    _colors.push_back(color);
    }

sf::Color GraphInfo::generateDistinctColor()
    {
    return distinctColors[rand() % distinctColors.size()];
    }

void GraphInfo::setMode(Mode mode)
    {
    _mode = mode;
    }

GraphInfo::Mode GraphInfo::getMode()
    {
    return _mode;
    }

void GraphInfo::evaluateMode(const string& equation)
    {
    if (equation.find("theta") != string::npos || equation.find("θ") != string::npos)
        {
        setMode(POLAR);
        }
    else
        {
        setMode(CARTESIAN);
        }
    }


void GraphInfo::toggleMode()
    {
    if (_mode == CARTESIAN)
        {
        setMode(POLAR);
        }
    else
        {
        setMode(CARTESIAN);
        }
    }

vector<vector<sf::Vector2f>> GraphInfo::getPointsData() const // 新增方法
    {
    return _pointsData;
    }

void GraphInfo::setPointsData(const vector<vector<sf::Vector2f>>& pointsData) // 新增方法
    {
    _pointsData = pointsData;
    }