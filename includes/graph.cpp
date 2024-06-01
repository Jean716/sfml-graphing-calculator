#include "graph.h"
#include "plot.h"
#include "graphInfo.h"



Graph::Graph() : _info(nullptr), _plotter(nullptr), _points()
    {
    }

Graph::Graph(GraphInfo* info, const string& equation)
    : _info(info), _plotter(info)
    {
    if (_info == nullptr)
        {
        cerr << "Error: GraphInfo pointer is null!" << endl;
        return;
        }
    _info->getEquation() = equation;
    // update(equation);



    }

void Graph::update(const string& equation)
    {

    // if (_info == nullptr)
    //     {
    //     cerr << "Error: Graphinfo pointer is null!" << endl;
    //     return;
    //     }

    // _info->getEquation() = equation;
    // _points = _plotter(-10, 10, 0.1f);

    }

void Graph::draw(sf::RenderWindow& window)
    {
    // draw the x-axis
    sf::Vertex xAxis[] =
        {
            sf::Vertex(sf::Vector2f(0, 400), sf::Color::Black), // set the left point of the x-axis
            sf::Vertex(sf::Vector2f(1120, 400), sf::Color::Black) // set the right point of the x-axis
        };

    // draw the y-axis
    sf::Vertex yAxis[] =
        {
            sf::Vertex(sf::Vector2f(560, 0), sf::Color::Black), // set the top point of the y-axis
            sf::Vertex(sf::Vector2f(560, 800), sf::Color::Black) // set the bottom point of the y-axis
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


