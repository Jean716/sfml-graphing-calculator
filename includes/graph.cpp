#include "graph.h"
#include "plot.h"
#include "graphInfo.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include "coord_translation.h"
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

Graph::Graph() : _info(nullptr), _plot(nullptr), _coordTranslation(nullptr), _polar() {}

Graph::Graph(GraphInfo* info)
    : _info(info), _plot(info), _coordTranslation(info), _polar()
    {
    generatePoints();
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/
void Graph::set_info(GraphInfo* info)
    {
    std::cout << "Graph::set_info is Fired" << std::endl;
    _info = info;
    _plot.set_info(info);
    _coordTranslation.set_info(info);
    _polar.set_info(info);
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Graph::update(GraphInfo* info)
    {
    set_info(info);
    generatePoints();
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Graph::draw(sf::RenderWindow& window)
    {
    if (_info->_mode == GraphInfo::CARTESIAN)
        {
        drawCartesian(window);
        }
    else if (_info->_mode == GraphInfo::POLAR)
        {
        _polar.draw(window, _info);

        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Graph::drawCartesian(sf::RenderWindow& window)
    {
    drawAxes(window);
    drawTicksAndLabels(window);
    drawGraphPoints(window);
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Graph::drawAxes(sf::RenderWindow& window)
    {
    float scale = _info->_scale;
    sf::Vector2f origin = _info->_origin;
    float offsetX = _info->_offsetX;
    float offsetY = _info->_offsetY;

    sf::Vertex xAxis[] = {
        sf::Vertex(sf::Vector2f(0, origin.y + offsetY), sf::Color::Black),
        sf::Vertex(sf::Vector2f(window.getSize().x, origin.y + offsetY), sf::Color::Black)
        };
    window.draw(xAxis, 2, sf::Lines);

    sf::Vertex yAxis[] = {
        sf::Vertex(sf::Vector2f(origin.x + offsetX, 0), sf::Color::Black),
        sf::Vertex(sf::Vector2f(origin.x + offsetX, window.getSize().y), sf::Color::Black)
        };
    window.draw(yAxis, 2, sf::Lines);
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Graph::drawTicksAndLabels(sf::RenderWindow& window)
    {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        {
        // handle error
        }

    float scale = _info->_scale;
    sf::Vector2f origin = _info->_origin;
    float offsetX = _info->_offsetX;
    float offsetY = _info->_offsetY;

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
            drawTickAndLabel(window, font, graphX, scale, origin, offsetX, offsetY);
            }
        }

    for (float graphY = 0; graphY * scale < window.getSize().y / 2; ++graphY)
        {
        if (graphY != 0)
            {
            drawTickAndLabel(window, font, graphY, scale, origin, offsetX, offsetY, true);
            }
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Graph::drawTickAndLabel(sf::RenderWindow& window, const sf::Font& font, float graphValue, float scale, const sf::Vector2f& origin, float offsetX, float offsetY, bool isYAxis)
    {
    sf::Vector2f screenPos;
    sf::Vertex tick[2];

    if (isYAxis)
        {
        screenPos = sf::Vector2f(origin.x + offsetX, origin.y - graphValue * scale + offsetY);
        tick[0] = sf::Vertex(sf::Vector2f(origin.x + offsetX - 5, screenPos.y), sf::Color::Black);
        tick[1] = sf::Vertex(sf::Vector2f(origin.x + offsetX + 5, screenPos.y), sf::Color::Black);
        }
    else
        {
        screenPos = sf::Vector2f(origin.x + graphValue * scale + offsetX, origin.y + offsetY);
        tick[0] = sf::Vertex(sf::Vector2f(screenPos.x, origin.y + offsetY - 5), sf::Color::Black);
        tick[1] = sf::Vertex(sf::Vector2f(screenPos.x, origin.y + offsetY + 5), sf::Color::Black);
        }

    window.draw(tick, 2, sf::Lines);

    sf::Text label;
    label.setFont(font);
    label.setCharacterSize(15);
    label.setFillColor(sf::Color::Black);
    label.setString(std::to_string(static_cast<int>(graphValue)));

    if (isYAxis)
        {
        label.setPosition(origin.x + offsetX + 10, screenPos.y);
        }
    else
        {
        label.setPosition(screenPos.x, origin.y + offsetY + 10);
        }

    window.draw(label);

    if (!isYAxis)
        {
        screenPos = sf::Vector2f(origin.x - graphValue * scale + offsetX, origin.y + offsetY);
        tick[0].position = sf::Vector2f(screenPos.x, origin.y + offsetY - 5);
        tick[1].position = sf::Vector2f(screenPos.x, origin.y + offsetY + 5);
        window.draw(tick, 2, sf::Lines);

        label.setString("-" + std::to_string(static_cast<int>(graphValue)));
        label.setPosition(screenPos.x, origin.y + offsetY + 10);
        window.draw(label);
        }
    else
        {
        screenPos = sf::Vector2f(origin.x + offsetX, origin.y + graphValue * scale + offsetY);
        tick[0].position = sf::Vector2f(origin.x + offsetX - 5, screenPos.y);
        tick[1].position = sf::Vector2f(origin.x + offsetX + 5, screenPos.y);
        window.draw(tick, 2, sf::Lines);

        label.setString("-" + std::to_string(static_cast<int>(graphValue)));
        label.setPosition(origin.x + offsetX + 10, screenPos.y);
        window.draw(label);
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Graph::drawGraphPoints(sf::RenderWindow& window)
    {
    std::vector<sf::Color> colors = _info->_colors;
    for (size_t eqIndex = 0; eqIndex < _points.size(); ++eqIndex)
        {
        for (const auto& point : _points[eqIndex])
            {
            sf::CircleShape shape(2);
            shape.setPosition(point);
            if (_info->_currentFunctionIndex == eqIndex)
                {
                shape.setFillColor(sf::Color::Red);
                shape.setRadius(2); // 
                }
            else
                {
                shape.setFillColor(colors[eqIndex]);
                }
            window.draw(shape);
            }
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Graph::generatePoints()
    {
    if (_info)
        {
        _points = _plot(_info->_domain.x, _info->_domain.y, 0.1f);
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Graph::drawDomainAndCoordinate(sf::RenderWindow& window)
    {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        {
        // handle error
        }

    sf::Text domainText;
    domainText.setFont(font);
    domainText.setCharacterSize(15);
    domainText.setFillColor(sf::Color::Black);

    sf::Text coordinateText;
    coordinateText.setFont(font);
    coordinateText.setCharacterSize(15);
    coordinateText.setFillColor(sf::Color::Black);

    stringstream domainStream;
    stringstream coordinateStream;

    if (_info->_mode == GraphInfo::CARTESIAN)
        {
        domainStream << "Domain: [" << _info->_domain.x << ", " << _info->_domain.y << "]";
        coordinateStream << "Cartesian Coordinate: (" << _info->_origin.x << ", " << _info->_origin.y << ")";
        }
    else if (_info->_mode == GraphInfo::POLAR)
        {
        domainStream << "Domain: [0, 2π]";
        coordinateStream << "Polar Coordinate: (r, θ)";
        }

    domainText.setString(domainStream.str());
    domainText.setPosition(10, 10);
    window.draw(domainText);

    coordinateText.setString(coordinateStream.str());
    coordinateText.setPosition(10, 30);
    window.draw(coordinateText);
    }

//*------------------------------------------------------- DIVISION -------------------------------------------------------*/
void Graph::drawGrid(sf::RenderWindow & window)
    {
    sf::VertexArray lines(sf::Lines);

    const float step = _info->_scale;
    const sf::Color gridColor(200, 200, 200);

    sf::Vector2f origin = _info->_origin;
    float offsetX = _info->_offsetX;
    float offsetY = _info->_offsetY;
    float scale = _info->_scale;


    for (float x = origin.x + offsetX; x < WORK_PANEL; x += step)
        {
        lines.append(sf::Vertex(sf::Vector2f(x, 0), gridColor));
        lines.append(sf::Vertex(sf::Vector2f(x, SCREEN_HEIGHT), gridColor));
        }
    for (float x = origin.x + offsetX; x > 0; x -= step)
        {
        lines.append(sf::Vertex(sf::Vector2f(x, 0), gridColor));
        lines.append(sf::Vertex(sf::Vector2f(x, SCREEN_HEIGHT), gridColor));
        }


    for (float y = origin.y + offsetY; y < SCREEN_HEIGHT; y += step)
        {
        lines.append(sf::Vertex(sf::Vector2f(0, y), gridColor));
        lines.append(sf::Vertex(sf::Vector2f(WORK_PANEL, y), gridColor));
        }
    for (float y = origin.y + offsetY; y > 0; y -= step)
        {
        lines.append(sf::Vertex(sf::Vector2f(0, y), gridColor));
        lines.append(sf::Vertex(sf::Vector2f(WORK_PANEL, y), gridColor));
        }

    window.draw(lines);
    }



