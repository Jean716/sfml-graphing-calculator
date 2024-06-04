#ifndef GRAPHINFO_H
#define GRAPHINFO_H

#include <SFML/Graphics.hpp>
#include <string>
#include "constants.h"
#include <iostream>
using namespace std;

class GraphInfo
    {
    public:
        // Default constructor
        GraphInfo()
            : _equation(""), _windowDimensions(SCREEN_WIDTH, SCREEN_HEIGHT),
            _origin(WORK_PANEL / 2, SCREEN_HEIGHT / 2), _domain(DEFAULT_DOMAIN),
            _scale(DEFAULT_SCALE), _points(DEFAULT_POINTS), _offsetX(DEFAULT_OFFSET_X), _offsetY(DEFAULT_OFFSET_Y)
            {
            }

        // Getter and Setter methods
        string getEquation() const { return _equation; }
        void setEquation(const string& equation) { _equation = equation; }

        sf::Vector2f getDomain() const { return _domain; }
        void setDomain(const sf::Vector2f& domain) { _domain = domain; }

        sf::Vector2f getOrigin() const { return _origin; }
        void setOrigin(const sf::Vector2f& origin) { _origin = origin; }

        float getScale() const { return _scale; }
        void setScale(float scale) { _scale = scale; }

        float getPoint() const { return _points; }
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

    private:
        string _equation;           // Equation of the graph
        sf::Vector2f _windowDimensions; // Window dimensions
        sf::Vector2f _origin;            // Origin of the graph
        sf::Vector2f _domain;            // Domain of the graph
        float _scale;                    // Scale of the graph
        int _points;                     // Number of points in the graph
        float _offsetX;                  // X-axis offset for panning
        float _offsetY;                  // Y-axis offset for panning
        vector<sf::Vertex> _vertices; // Vertices for drawing the graph
    };

#endif 