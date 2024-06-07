#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "plot.h"
#include <SFML/Graphics.hpp>
#include "coord_translation.h"
#include <string>

using namespace std;
// Graphinfo class is to store the information of the graph
// initialize the graph with the equation
// plot the graph based on the equation 

using namespace std;
class Graph
    {
    public:
        Graph();
        Graph(GraphInfo* info); // function<float(float)> means a function that takes a float and returns a float
        void update(GraphInfo* info);  // This function will be used to update the graph
        void draw(sf::RenderWindow& window); //  This function will be used to draw the graph
        void set_info(GraphInfo* info); // set the information of the graph
    private:
        GraphInfo* _info; //  graph information
        vector<vector<sf::Vector2f>> _points; //  store the points of the graph
        Plot _plot; //  plot object
        CoordTranslation _coordTranslation;
        void generatePoints(); // call the plot object to generate the points
        sf::Font _font;
    };

#endif


/*
vector< > is a container that can hold a dynamic number of elements
vector<sf::Vector2f> means that a vector that can hold 2D points
*/