#include "graph.h"
#include "plot.h"
#include "graphInfo.h"
#include "coord_translation.h"

Graph::Graph() : _info(nullptr), _plot(nullptr), _coordTranslation(nullptr)
    {
    }

Graph::Graph(GraphInfo* info)
    : _info(info), _plot(info), _coordTranslation(info)
    {
    generatePoints();
    }

void Graph::set_info(GraphInfo* info)
    {
    _info = info;
    _plot.set_info(info);
    _coordTranslation.set_info(info);
    }

void Graph::update(GraphInfo* info)
    {
    set_info(info);
    generatePoints();
    }

void Graph::draw(sf::RenderWindow& window)
    {
    // draw the x-axis
    sf::Vertex xAxis[] =
        {
            sf::Vertex(sf::Vector2f(0, 400), sf::Color::Green), // set the left point of the x-axis
            sf::Vertex(sf::Vector2f(1120, 400), sf::Color::Green) // set the right point of the x-axis
        };

    // draw the y-axis
    sf::Vertex yAxis[] =
        {
            sf::Vertex(sf::Vector2f(560, 0), sf::Color::Green), // set the top point of the y-axis
            sf::Vertex(sf::Vector2f(560, 800), sf::Color::Green) // set the bottom point of the y-axis
        };

    window.draw(xAxis, 2, sf::Lines); // Lines is the type of the shape
    window.draw(yAxis, 2, sf::Lines); // draw the x-axis and y-axis

    // draw the function
    for (const auto& point : _points)
        {
        sf::CircleShape shape(2); // the radius of the circle is 2
        shape.setPosition(point); // the position of the circle is the point
        shape.setFillColor(sf::Color::Red); // the color of the circle is red
        window.draw(shape); // draw the circle
        }
    }

void Graph::generatePoints()
    {
    if (_info)
        {
        _points = _plot(_info->getDomain().x, _info->getDomain().y, 0.1f); // generate the points of the graph
        }
    }
