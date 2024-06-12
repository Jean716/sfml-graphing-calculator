#include "graph.h"
#include "plot.h"
#include "graphInfo.h"
#include <cmath>

#include "coord_translation.h"

Graph::Graph() : _info(nullptr), _plot(nullptr), _coordTranslation(nullptr)//, _polar()
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
    if (_info->getMode() == GraphInfo::CARTESIAN)
        {

        float scale = _info->getScale();
        sf::Vector2f origin = _info->getOrigin();
        float offsetX = _info->getOffsetX();
        float offsetY = _info->getOffsetY();
        sf::Font font;

        if (!font.loadFromFile("arial.ttf"))
            {

            }

        float tickSpacing = scale;


        sf::Vertex xAxis[] =
            {
                sf::Vertex(sf::Vector2f(0, origin.y + offsetY), sf::Color::Black),
                sf::Vertex(sf::Vector2f(window.getSize().x, origin.y + offsetY), sf::Color::Black)
            };
        window.draw(xAxis, 2, sf::Lines);


        sf::Vertex yAxis[]
            {
                sf::Vertex(sf::Vector2f(origin.x + offsetX, 0), sf::Color::Black),
                sf::Vertex(sf::Vector2f(origin.x + offsetX, window.getSize().y), sf::Color::Black)
            };
        window.draw(yAxis, 2, sf::Lines);


        sf::Text originLabel;
        originLabel.setFont(font);
        originLabel.setCharacterSize(15);
        originLabel.setFillColor(sf::Color::Black);
        originLabel.setString("0");
        originLabel.setPosition(origin.x + offsetX + 5, origin.y + offsetY + 5);
        window.draw(originLabel);


        for (float graphX = 0; graphX * scale < window.getSize().x / 2; ++graphX)
            {
            if (graphX != 0)
                {

                sf::Vector2f screenPos = sf::Vector2f(origin.x + graphX * scale + offsetX, origin.y + offsetY);
                sf::Vertex tick[] =
                    {
                        sf::Vertex(sf::Vector2f(screenPos.x, origin.y + offsetY - 5), sf::Color::Black),
                        sf::Vertex(sf::Vector2f(screenPos.x, origin.y + offsetY + 5), sf::Color::Black)
                    };
                window.draw(tick, 2, sf::Lines);

                sf::Text label;
                label.setFont(font);
                label.setCharacterSize(15);
                label.setFillColor(sf::Color::Black);
                label.setString(std::to_string(static_cast<int>(graphX)));
                label.setPosition(screenPos.x, origin.y + offsetY + 10);
                window.draw(label);


                screenPos = sf::Vector2f(origin.x - graphX * scale + offsetX, origin.y + offsetY);
                tick[0].position = sf::Vector2f(screenPos.x, origin.y + offsetY - 5);
                tick[1].position = sf::Vector2f(screenPos.x, origin.y + offsetY + 5);
                window.draw(tick, 2, sf::Lines);

                label.setString("-" + std::to_string(static_cast<int>(graphX)));
                label.setPosition(screenPos.x, origin.y + offsetY + 10);
                window.draw(label);
                }
            }


        for (float graphY = 0; graphY * scale < window.getSize().y / 2; ++graphY)
            {
            if (graphY != 0)
                {

                sf::Vector2f screenPos = sf::Vector2f(origin.x + offsetX, origin.y - graphY * scale + offsetY);
                sf::Vertex tick[] =
                    {
                        sf::Vertex(sf::Vector2f(origin.x + offsetX - 5, screenPos.y), sf::Color::Black),
                        sf::Vertex(sf::Vector2f(origin.x + offsetX + 5, screenPos.y), sf::Color::Black)
                    };
                window.draw(tick, 2, sf::Lines);

                sf::Text label;
                label.setFont(font);
                label.setCharacterSize(15);
                label.setFillColor(sf::Color::Black);
                label.setString(std::to_string(static_cast<int>(graphY)));
                label.setPosition(origin.x + offsetX + 10, screenPos.y);
                window.draw(label);


                screenPos = sf::Vector2f(origin.x + offsetX, origin.y + graphY * scale + offsetY);
                tick[0].position = sf::Vector2f(origin.x + offsetX - 5, screenPos.y);
                tick[1].position = sf::Vector2f(origin.x + offsetX + 5, screenPos.y);
                window.draw(tick, 2, sf::Lines);

                label.setString("-" + to_string(static_cast<int>(graphY)));
                label.setPosition(origin.x + offsetX + 10, screenPos.y);
                window.draw(label);
                }
            }


        vector<sf::Color> colors = _info->getColors();
        for (size_t eqIndex = 0; eqIndex < _points.size(); ++eqIndex)
            {
            for (const auto& point : _points[eqIndex])
                {
                sf::CircleShape shape(2);
                shape.setPosition(point);
                shape.setFillColor(colors[eqIndex]);
                window.draw(shape);
                }
            }
        }
    }


void Graph::generatePoints()
    {
    if (_info)
        {
        _points = _plot(_info->getDomain().x, _info->getDomain().y, 0.1f);
        }
    }