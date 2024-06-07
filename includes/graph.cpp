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
    cout << "Graph::set_info is Fired" << endl;
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
    // get the current scale, origin, offsetX, offsetY
    float scale = _info->getScale();
    sf::Vector2f origin = _info->getOrigin();
    float offsetX = _info->getOffsetX();
    float offsetY = _info->getOffsetY();


    // draw the x-axis
    sf::Vertex xAxis[] =
        {
            sf::Vertex(sf::Vector2f(0, origin.y + offsetY), sf::Color::Green),
            sf::Vertex(sf::Vector2f(SCREEN_WIDTH, origin.y + offsetY), sf::Color::Green)
        };


    // draw the y-axis
    sf::Vertex yAxis[] =
        {
            sf::Vertex(sf::Vector2f(origin.x + offsetX, 0), sf::Color::Green),
            sf::Vertex(sf::Vector2f(origin.x + offsetX, SCREEN_HEIGHT), sf::Color::Green)
        };

    window.draw(xAxis, 2, sf::Lines);
    window.draw(yAxis, 2, sf::Lines);

    // Draw tick marks on the x-axis
    for (float x = origin.x + offsetX; x < SCREEN_WIDTH; x += scale)
        {
        sf::Vertex tick[] =
            {
                sf::Vertex(sf::Vector2f(x, origin.y + offsetY - 5), sf::Color::White),
                sf::Vertex(sf::Vector2f(x, origin.y + offsetY + 5), sf::Color::White)
            };
        window.draw(tick, 2, sf::Lines);
        }

    for (float x = origin.x + offsetX; x > 0; x -= scale)
        {
        sf::Vertex tick[] =
            {
                sf::Vertex(sf::Vector2f(x, origin.y + offsetY - 5), sf::Color::White),
                sf::Vertex(sf::Vector2f(x, origin.y + offsetY + 5), sf::Color::White)
            };
        window.draw(tick, 2, sf::Lines);
        }

    // Draw tick marks on the y-axis
    for (float y = origin.y + offsetY; y < SCREEN_HEIGHT; y += scale)
        {
        sf::Vertex tick[] =
            {
                sf::Vertex(sf::Vector2f(origin.x + offsetX - 5, y), sf::Color::White),
                sf::Vertex(sf::Vector2f(origin.x + offsetX + 5, y), sf::Color::White)
            };
        window.draw(tick, 2, sf::Lines);
        }

    for (float y = origin.y + offsetY; y > 0; y -= scale)
        {
        sf::Vertex tick[] =
            {
                sf::Vertex(sf::Vector2f(origin.x + offsetX - 5, y), sf::Color::White),
                sf::Vertex(sf::Vector2f(origin.x + offsetX + 5, y), sf::Color::White)
            };
        window.draw(tick, 2, sf::Lines);
        }

    // draw the function
    for (const auto& point : _points)
        {
        sf::CircleShape shape(2);
        shape.setPosition(point);
        shape.setFillColor(sf::Color::Red);
        window.draw(shape);
        }
    }



void Graph::generatePoints()
    {
    if (_info)
        {
        _points = _plot(_info->getDomain().x, _info->getDomain().y, 0.1f); // generate the points of the graph
        }
    }
