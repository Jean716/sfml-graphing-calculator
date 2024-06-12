#ifndef GRAPHINFO_H
#define GRAPHINFO_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "constants.h"

using namespace std;

struct GraphInfo
    {
    public:
        enum Mode
            {
            INPUT,
            ZOOM,
            PAN,
            CARTESIAN,
            POLAR
            };


        // Default constructor
        GraphInfo();

        // Getter and Setter methods
        vector<string> getEquations() const;
        vector<sf::Color> getColors() const;
        void addEquation(const string& equation);
        void setEquation(const string& equation);
        void removeEquation(size_t index);

        sf::Vector2f getDomain() const;
        void setDomain(const sf::Vector2f& domain);

        sf::Vector2f getOrigin() const;
        void setOrigin(const sf::Vector2f& origin);

        float getScale() const;
        void setScale(float scale);

        float getPoints() const;
        void setPoints(int points);

        float getOffsetX() const;
        void setOffsetX(float offsetX);

        float getOffsetY() const;
        void setOffsetY(float offsetY);

        vector<sf::Vertex> getVertices() const;
        void setVertices(const vector<sf::Vertex>& vertices);

        void zoom(float factor);
        void pan(float deltaX, float deltaY);
        void setColor(const sf::Color& color);

        sf::Color generateDistinctColor();

        void setMode(Mode mode);
        Mode getMode();
        void evaluateMode(const string& equation);
        void toggleMode();

        vector<string> _equations;          // Equation of the graph
        vector<sf::Color> _colors;          // Color of the graph
        sf::Vector2f _windowDimensions;     // Window dimensions
        sf::Vector2f _origin;               // Origin of the graph
        sf::Vector2f _domain;               // Domain of the graph
        float _scale;                       // Scale of the graph
        int _points;                        // Number of points in the graph
        float _offsetX;                     // X-axis offset for panning
        float _offsetY;                     // Y-axis offset for panning
        vector<sf::Vertex> _vertices;       // Vertices for drawing the graph
        Mode _mode;                         // Mode of the graph
        vector<vector<sf::Vector2f>> getPointsData() const;  // 新增
        void setPointsData(const vector<vector<sf::Vector2f>>& pointsData);  // 新增

        const vector<sf::Color> distinctColors = {
            sf::Color(210, 176, 251), // light purple
            sf::Color(131, 175, 155), // light green
            sf::Color(241, 196, 15),  // Yellow
            sf::Color(228, 68, 52),   // Red
            sf::Color(142, 68, 173),  // Purple
            sf::Color(211, 84, 0),    // Orange
            // sf::Color(41, 128, 185)   // Blue
            };


    private:
        vector<vector<sf::Vector2f>> _pointsData;  // 新增成员变量
    };

#endif