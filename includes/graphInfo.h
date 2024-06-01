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
            : _equation(""), _window_dimensions(SCREEN_WIDTH, SCREEN_HEIGHT),
            _origin(WORK_PANEL / 2, SCREEN_HEIGHT / 2), _domain(-5, 5),
            _scale(1.0f), _points(100)
            {
            }

        // Parameterized constructor
        GraphInfo(const std::string& equation, const sf::Vector2f& windowDimensions,
            const sf::Vector2f& origin, const sf::Vector2f& domain,
            float scale, int points)
            : _equation(equation), _window_dimensions(windowDimensions),
            _origin(origin), _domain(domain), _scale(scale), _points(points)
            {
            }

        // Getter and Setter methods
        std::string getEquation() const { return _equation; }
        void setEquation(const std::string& equation) { _equation = equation; }

        sf::Vector2f getWindowDimensions() const { return _window_dimensions; }
        void setWindowDimensions(const sf::Vector2f& windowDimensions) { _window_dimensions = windowDimensions; }

        sf::Vector2f getOrigin() const { return _origin; }
        void setOrigin(const sf::Vector2f& origin) { _origin = origin; }

        sf::Vector2f getDomain() const { return _domain; }
        void setDomain(const sf::Vector2f& domain) { _domain = domain; }

        float getScale() const { return _scale; }
        void setScale(float scale) { _scale = scale; }

        int getPoints() const { return _points; }
        void setPoints(int points) { _points = points; }

    private:
        std::string _equation;           // Equation of the graph
        sf::Vector2f _window_dimensions; // Window dimensions
        sf::Vector2f _origin;            // Origin of the graph
        sf::Vector2f _domain;            // Domain of the graph
        float _scale;                    // Scale of the graph
        int _points;                     // Number of points in the graph
    };

#endif 