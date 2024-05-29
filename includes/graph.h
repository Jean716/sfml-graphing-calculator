#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <functional>

using namespace std;
class Graph
    {
    public:
        Graph(const function<float(float)>& func); // function<float(float)> means a function that takes a float and returns a float
        void update(const function<float(float)>& func);  // This function will be used to update the graph
        void draw(sf::RenderWindow& window); //  This function will be used to draw the graph

    private:
        vector<sf::Vector2f> _points; //  Vector2f is a 2D vector with float values
        // vector< > is a container that can hold a dynamic number of elements

       //vector<sf::Vector2f> means that a vector that can hold 2D points
    };

#endif