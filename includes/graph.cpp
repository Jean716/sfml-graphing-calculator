#include "graph.h"

Graph::Graph(const function<float(float)>& func)
    {
    update(func);
    }
void Graph::update(const function<float(float)>& func)
    {
    _points.clear(); //   clear the vector of points

    // generate the points and transform them to screen coordinates
    for (float x = -10; x <= 10; x += 0.1f)
        {
        float y = func(x); //  calculate the y value of the function
        float screenX = x * 56 + 560; //  the x position of the point
        float screenY = -y * 56 + 400; //  the y position of the point
        _points.push_back(sf::Vector2f(screenX, screenY)); //  add the point to the vector

        }

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
