#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "plot.h"
#include "graphInfo.h"
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
        Graph(GraphInfo* info, const string& equation); // function<float(float)> means a function that takes a float and returns a float
        void update(const string& equation);  // This function will be used to update the graph
        void draw(sf::RenderWindow& window); //  This function will be used to draw the graph

    private:
        vector<sf::Vector2f> _points; //  screen points, Vector2f is a 2D vector with float value
        Plot _plotter;
        GraphInfo* _info;

        // vector< > is a container that can hold a dynamic number of elements

       //vector<sf::Vector2f> means that a vector that can hold 2D points
    };

#endif



