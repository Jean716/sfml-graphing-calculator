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
    // get the scale, origin, and offset of the graph
    float scale = _info->getScale();
    sf::Vector2f origin = _info->getOrigin();
    float offsetX = _info->getOffsetX();
    float offsetY = _info->getOffsetY();
    sf::Font font;

    if (!font.loadFromFile("arial.ttf"))
        {
        // handle error
        }

    // draw x axis
    sf::Vertex xAxis[] =
        {
            sf::Vertex(sf::Vector2f(0, origin.y + offsetY), sf::Color::Green),
            sf::Vertex(sf::Vector2f(SCREEN_WIDTH, origin.y + offsetY), sf::Color::Green)
        };

    // draw y axis
    sf::Vertex yAxis[] =
        {
            sf::Vertex(sf::Vector2f(origin.x + offsetX, 0), sf::Color::Green),
            sf::Vertex(sf::Vector2f(origin.x + offsetX, SCREEN_HEIGHT), sf::Color::Green)
        };

    window.draw(xAxis, 2, sf::Lines);
    window.draw(yAxis, 2, sf::Lines);

    // draw origin
    sf::Text originLabel;
    originLabel.setFont(font);
    originLabel.setCharacterSize(15);
    originLabel.setFillColor(sf::Color::White);
    originLabel.setString("0");
    originLabel.setPosition(origin.x + offsetX + 5, origin.y + offsetY + 5);
    window.draw(originLabel);

    // set the tick spacing based on the scale
    float tickSpacing = scale; // 1 unit on the graph is equal to 1 pixel on the screen

    // draw x axis ticks and labels
    for (float x = origin.x; x < SCREEN_WIDTH; x += tickSpacing)
        {
        sf::Vector2f screenPos = _coordTranslation.translate(sf::Vector2f((x - origin.x) / scale, 0));

        if (static_cast<int>(screenPos.x) == static_cast<int>(origin.x + offsetX)) continue; // skip the origin

        sf::Vertex tick[] =
            {
                sf::Vertex(sf::Vector2f(screenPos.x, origin.y + offsetY - 5), sf::Color::White),
                sf::Vertex(sf::Vector2f(screenPos.x, origin.y + offsetY + 5), sf::Color::White)
            };
        window.draw(tick, 2, sf::Lines);

        sf::Text label;
        label.setFont(font);
        label.setCharacterSize(10);
        label.setFillColor(sf::Color::White);
        label.setString(to_string(static_cast<int>((x - origin.x) / scale)));
        label.setPosition(screenPos.x, origin.y + offsetY + 10);
        window.draw(label);
        }

    for (float x = origin.x; x > 0; x -= tickSpacing)
        {
        sf::Vector2f screenPos = _coordTranslation.translate(sf::Vector2f((x - origin.x) / scale, 0));

        if (static_cast<int>(screenPos.x) == static_cast<int>(origin.x + offsetX)) continue; // skip the origin

        sf::Vertex tick[] =
            {
                sf::Vertex(sf::Vector2f(screenPos.x, origin.y + offsetY - 5), sf::Color::White),
                sf::Vertex(sf::Vector2f(screenPos.x, origin.y + offsetY + 5), sf::Color::White)
            };
        window.draw(tick, 2, sf::Lines);

        sf::Text label;
        label.setFont(font);
        label.setCharacterSize(15);
        label.setFillColor(sf::Color::White);
        label.setString(to_string(static_cast<int>((x - origin.x) / scale)));
        label.setPosition(screenPos.x, origin.y + offsetY + 10);
        window.draw(label);
        }

    // draw y axis ticks and labels
    for (float y = origin.y; y < SCREEN_HEIGHT; y += tickSpacing)
        {
        sf::Vector2f screenPos = _coordTranslation.translate(sf::Vector2f(0, (origin.y - y) / scale));

        if (static_cast<int>(screenPos.y) == static_cast<int>(origin.y + offsetY)) continue;

        sf::Vertex tick[] =
            {
                sf::Vertex(sf::Vector2f(origin.x + offsetX - 5, screenPos.y), sf::Color::White),
                sf::Vertex(sf::Vector2f(origin.x + offsetX + 5, screenPos.y), sf::Color::White)
            };
        window.draw(tick, 2, sf::Lines);

        sf::Text label;
        label.setFont(font);
        label.setCharacterSize(15);
        label.setFillColor(sf::Color::White);
        label.setString(to_string(static_cast<int>((origin.y - y) / scale)));
        label.setPosition(origin.x + offsetX + 10, screenPos.y);
        window.draw(label);
        }

    for (float y = origin.y; y > 0; y -= tickSpacing)
        {
        sf::Vector2f screenPos = _coordTranslation.translate(sf::Vector2f(0, (origin.y - y) / scale));

        if (static_cast<int>(screenPos.y) == static_cast<int>(origin.y + offsetY)) continue; // 跳过原点

        sf::Vertex tick[] =
            {
                sf::Vertex(sf::Vector2f(origin.x + offsetX - 5, screenPos.y), sf::Color::White),
                sf::Vertex(sf::Vector2f(origin.x + offsetX + 5, screenPos.y), sf::Color::White)
            };
        window.draw(tick, 2, sf::Lines);

        sf::Text label;
        label.setFont(font);
        label.setCharacterSize(15);
        label.setFillColor(sf::Color::White);
        label.setString(to_string(static_cast<int>((origin.y - y) / scale)));
        label.setPosition(origin.x + offsetX + 10, screenPos.y);
        window.draw(label);
        }

    // draw the functions
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

void Graph::generatePoints()
    {
    if (_info)
        {
        _points = _plot(_info->getDomain().x, _info->getDomain().y, 0.1f); // generate the points of the graph
        }
    }