#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "plot.h"
#include <SFML/Graphics.hpp>
#include "coord_translation.h"
#include <string>
#include "graphInfo.h"
#include "polar.h"

using namespace std;

class Graph
    {
    public:
        Graph(); // Constructor
        Graph(GraphInfo* info); // Parameterized constructor

        void update(GraphInfo* info);  // This function will be used to update the graph
        void draw(sf::RenderWindow& window); // This function will be used to draw the graph
        void set_info(GraphInfo* info); // Set the information of the graph
        void drawGrid(sf::RenderWindow& window);


    private:
        GraphInfo* _info; // Graph information
        vector<vector<sf::Vector2f>> _points; // Store the points of the graph
        Plot _plot; // Plot object
        Polar _polar;
        CoordTranslation _coordTranslation;
        void generatePoints(); // Call the plot object to generate the points
        void drawCartesian(sf::RenderWindow& window); // Draw the Cartesian graph
        void drawAxes(sf::RenderWindow& window); // Draw the axes for the Cartesian graph
        void drawTicksAndLabels(sf::RenderWindow& window); // Draw ticks and labels for the Cartesian graph
        void drawTickAndLabel(sf::RenderWindow& window, const sf::Font& font, float graphValue, float scale, const sf::Vector2f& origin, float offsetX, float offsetY, bool isYAxis = false); // Helper function to draw individual ticks and labels
        void drawGraphPoints(sf::RenderWindow& window); // Draw the graph points
        void drawDomainAndCoordinate(sf::RenderWindow& window);
    };

#endif