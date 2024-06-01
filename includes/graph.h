#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "plot.h"
#include "graphInfo.h"
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
        //void plot();
        //sf::Vector2f translateMouseCoords(const sf::Vector2f& points) const;
        ;
    private:
        vector<sf::Vector2f> _points; //  store the points of the graph
        Plot _plot; //  plot object
        GraphInfo* _info; //  graph information
        CoordTranslation _coordTranslation;

    };

#endif


/*
vector< > is a container that can hold a dynamic number of elements
vector<sf::Vector2f> means that a vector that can hold 2D points
*/
