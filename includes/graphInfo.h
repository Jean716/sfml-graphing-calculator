#ifndef GRAPHINFO_H
#define GRAPHINFO_H

#include <SFML/Graphics.hpp>
#include <string>
#include "constants.h"
#include <iostream>
using namespace std;

struct GraphInfo
    {
    public:
        // Default constructor
        GraphInfo()
            : _windowDimensions(SCREEN_WIDTH, SCREEN_HEIGHT),
            _origin(WORK_PANEL / 2, SCREEN_HEIGHT / 2), _domain(DEFAULT_DOMAIN),
            _scale(DEFAULT_SCALE), _points(DEFAULT_POINTS), _offsetX(DEFAULT_OFFSET_X),
            _offsetY(DEFAULT_OFFSET_Y), hasParenError(false)
            {
            }
        // Getter and Setter methods
        vector<string> getEquations() const
            {
            return _equations;
            }
        vector<sf::Color> getColors() const
            {
            return _colors;
            }
        void addEquation(const string& equation)
            {
            _equations.push_back(equation);
            _colors.push_back(generateDistinctColor());
            }

        void setEquation(const string& equation)
            {
            cout << "Setting equation: " << equation << endl;

            _equations.clear();
            _equations.push_back(equation);
            }

        void removeEquation(size_t index)
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

        sf::Vector2f getDomain() const { return _domain; }
        void setDomain(const sf::Vector2f& domain) { _domain = domain; }

        sf::Vector2f getOrigin() const { return _origin; }
        void setOrigin(const sf::Vector2f& origin) { _origin = origin; }

        float getScale() const { return _scale; }
        void setScale(float scale) { _scale = scale; }

        float getPoints() const { return _points; }
        void setPoints(int points) { _points = points; }

        float getOffsetX() const { return _offsetX; }
        void setOffsetX(float offsetX) { _offsetX = offsetX; }

        float getOffsetY() const { return _offsetY; }
        void setOffsetY(float offsetY) { _offsetY = offsetY; }

        vector<sf::Vertex> getVertices() const { return _vertices; }
        void setVertices(const vector<sf::Vertex>& vertices) { _vertices = vertices; }

        void zoom(float factor)
            {
            _scale *= factor;
            cout << "Zoom: new scale = " << _scale << endl;
            }
        void pan(float deltaX, float deltaY)
            {
            _offsetX += deltaX;
            _offsetY += deltaY;
            cout << "Pan: new offset = (" << _offsetX << ", " << _offsetY << ")" << endl;
            }
        void setColor(const sf::Color& color)
            {
            _colors.clear();
            _colors.push_back(color);
            }


        sf::Color generateDistinctColor()
            {
            return distinctColors[rand() % distinctColors.size()];
            }
        bool hasParenError;

        vector<string> _equations;          // Equation of the graph
        vector<sf::Color> _colors;          // Color of the graph
        sf::Vector2f _windowDimensions; // Window dimensions
        sf::Vector2f _origin;            // Origin of the graph
        sf::Vector2f _domain;            // Domain of the graph
        float _scale;                    // Scale of the graph
        int _points;                     // Number of points in the graph
        float _offsetX;                  // X-axis offset for panning
        float _offsetY;                  // Y-axis offset for panning
        vector<sf::Vertex> _vertices; // Vertices for drawing the graph

        const vector<sf::Color> distinctColors = {
        sf::Color(210, 176, 251), // light purple
        sf::Color(131, 175, 155), //light green
        sf::Color(241, 196, 15),  // Yellow
        sf::Color(228, 68, 52),   // Red
        sf::Color(142, 68, 173),  // Purple
        sf::Color(211, 84, 0),    // Orange
        //sf::Color(41, 128, 185)   // Blue


            };
    };

#endif 