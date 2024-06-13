#include "polar.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

Polar::Polar() {}
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Polar::draw(sf::RenderWindow& window, GraphInfo* info)
    {
    drawPolarGrid(window, info);
    drawPolarLabels(window, info);
    drawPoints(window, info);


    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Polar::drawPolarGrid(sf::RenderWindow& window, GraphInfo* info)
    {
    float scale = info->_scale;
    sf::Vector2f origin = info->_origin;
    float offsetX = info->_offsetX;
    float offsetY = info->_offsetY;

    sf::CircleShape circle;
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(1);
    circle.setFillColor(sf::Color::Transparent);

    for (float r = scale; r < window.getSize().x; r += scale)
        {
        circle.setRadius(r);
        circle.setOrigin(r, r);
        circle.setPosition(origin.x + offsetX, origin.y + offsetY);
        window.draw(circle);
        }

    sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(origin.x + offsetX, 0), sf::Color::Black),
            sf::Vertex(sf::Vector2f(origin.x + offsetX, window.getSize().y), sf::Color::Black),
            sf::Vertex(sf::Vector2f(0, origin.y + offsetY), sf::Color::Black),
            sf::Vertex(sf::Vector2f(window.getSize().x, origin.y + offsetY), sf::Color::Black)
        };
    window.draw(line, 2, sf::Lines);
    window.draw(&line[2], 2, sf::Lines);
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Polar::drawPolarLabels(sf::RenderWindow& window, GraphInfo* info)
    {
    float scale = info->_scale;
    sf::Vector2f origin = info->_origin;
    float offsetX = info->_offsetX;
    float offsetY = info->_offsetY;
    sf::Font font;

    if (!font.loadFromFile("DejaVuSans.ttf"))
        {
        // handle error
        cerr << "Failed to load font!" << std::endl;
        return;
        }

    sf::Text label;
    label.setFont(font);
    label.setCharacterSize(15);
    label.setFillColor(sf::Color::Black);

    for (float r = scale; r < window.getSize().x; r += scale)
        {
        label.setString(std::to_string(static_cast<int>(r / scale)));
        label.setPosition(origin.x + offsetX + r, origin.y + offsetY);
        window.draw(label);
        }

    for (int angle = 0; angle < 360; angle += 30)
        {
        float radian = angle * M_PI / 180;
        std::string piLabel;

        switch (angle)
            {
                case 0:
                case 360:
                    piLabel = "0";
                    break;
                case 30:
                    piLabel = "π/6";
                    break;
                case 45:
                    piLabel = "π/4";
                    break;
                case 60:
                    piLabel = "π/3";
                    break;
                case 90:
                    piLabel = "π/2";
                    break;
                case 120:
                    piLabel = "2π/3";
                    break;
                case 135:
                    piLabel = "3π/4";
                    break;
                case 150:
                    piLabel = "5π/6";
                    break;
                case 180:
                    piLabel = "π";
                    break;
                case 210:
                    piLabel = "7π/6";
                    break;
                case 225:
                    piLabel = "5π/4";
                    break;
                case 240:
                    piLabel = "4π/3";
                    break;
                case 270:
                    piLabel = "3π/2";
                    break;
                case 300:
                    piLabel = "5π/3";
                    break;
                case 315:
                    piLabel = "7π/4";
                    break;
                case 330:
                    piLabel = "11π/6";
                    break;
                default:
                    piLabel = std::to_string(angle) + "°";
                    break;
            }

        std::wstring wpiLabel(piLabel.begin(), piLabel.end());
        label.setString(sf::String::fromUtf8(wpiLabel.begin(), wpiLabel.end()));

        float x = origin.x + offsetX + 100 * cos(radian);
        float y = origin.y + offsetY - 100 * sin(radian);
        label.setPosition(x, y);
        window.draw(label);
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Polar::drawPoints(sf::RenderWindow& window, GraphInfo* info)
    {
    vector<sf::Color> colors = info->_colors;
    vector<vector<sf::Vector2f>> points = info->getPointsData();

    for (size_t eqIndex = 0; eqIndex < points.size(); ++eqIndex)
        {
        for (const auto& point : points[eqIndex])
            {
            sf::CircleShape shape(2);
            shape.setPosition(point);
            shape.setFillColor(colors[eqIndex]);
            window.draw(shape);
            }
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Polar::set_info(GraphInfo* info)
    {
    _info = info;
    }


