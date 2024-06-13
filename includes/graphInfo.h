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


        //*------------------------------------------------------- DIVISION -------------------------------------------------------*/
        GraphInfo();
        //*------------------------------------------------------- DIVISION -------------------------------------------------------*/
        vector<string> _history;            // Equation of the graph
        vector<sf::Color> _colors;          // Color of the graph
        sf::Vector2f _windowDimensions;     // Window dimensions
        sf::Vector2f _origin;               // Origin of the graph
        sf::Vector2f _domain;               // Domain of the graph
        float _scale;                       // Scale of the graph
        float _offsetX;                     // X-axis offset for panning
        float _offsetY;                     // Y-axis offset for panning
        int _points;                        // Number of points in the graph
        Mode _mode;                         // Mode of the graph
        vector<sf::Vertex> _vertices;       // Vertices for drawing the graph
        vector<vector<sf::Vector2f>> _pointsData;
        vector<float> functionValues;
        int _currentFunctionIndex;          // Index of the currently selected function

        //*------------------------------------------------------- DIVISION -------------------------------------------------------*/

        void zoom(float factor);
        void pan(float deltaX, float deltaY);
        void panPolar(float dr);
        void adjustTheta(float dtheta);

        sf::Color generateDistinctColor();
        void evaluateMode(const string& equation);
        void toggleMode();
        string getFunctionPrefix() const;
        void setPointsData(const vector<vector<sf::Vector2f>>& pointsData);
        vector<vector<sf::Vector2f>> getPointsData() const;


        // string getCurrentFunction() const;
        // sf::Color getCurrentFunctionColor() const;
        //void setColor(const sf::Color& color);
        //void addEquation(const string& equation);
        // void removeEquation(size_t index);

    };

#endif