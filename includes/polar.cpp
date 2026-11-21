#include "font.h"
#include "polar.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cassert>
using namespace std;
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

Polar::Polar() : _info(nullptr) {}
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Polar::draw(sf::RenderWindow& window, GraphInfo* info)  // Draw the polar graph
    {
    drawPolarGrid(window, info);  //call the drawPolarGrid function
    drawPolarLabels(window, info);  //call the drawPolarLabels function
    drawPoints(window, info);  //call the drawPoints function

    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Polar::drawPolarGrid(sf::RenderWindow& window, GraphInfo* info)  // Draw the polar grid
    {
    float scale = info->_scale;  // Get the scale
    sf::Vector2f origin = info->_origin;  // Get the origin
    float offsetX = info->_offsetX;  // Get the offset x
    float offsetY = info->_offsetY;  // Get the offset y

    sf::CircleShape circle;  // Create a circle shape
    circle.setOutlineColor(sf::Color::Black);  // Set the outline color of the circle
    circle.setOutlineThickness(1);  // Set the outline thickness of the circle
    circle.setFillColor(sf::Color::Transparent);  // Set the fill color of the circle

    // Draw concentric circles
    for (float r = scale; r < window.getSize().x; r += scale)  // Iterate through the concentric circles
        {
        circle.setRadius(r);  // Set the radius of the circle
        circle.setOrigin(r, r);  // Set the origin of the circle
        circle.setPosition(origin.x + offsetX, origin.y + offsetY);  // Set the position of the circle
        window.draw(circle);  // Draw the circle
        }

    // Draw radial lines
    for (int angle = 0; angle < 360; angle += 30)  // Iterate through the angles
        {
        float radian = angle * M_PI / 180;  // Convert the angle to radians
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(origin.x + offsetX, origin.y + offsetY), sf::Color::Black),
            sf::Vertex(sf::Vector2f(origin.x + offsetX + cos(radian) * window.getSize().x, origin.y + offsetY - sin(radian) * window.getSize().y), sf::Color::Black)
            };
        window.draw(line, 2, sf::Lines);
        }

    // Draw X and Y axes
    sf::Vertex axes[] =
        {
            sf::Vertex(sf::Vector2f(origin.x + offsetX, 0), sf::Color::Black),
            sf::Vertex(sf::Vector2f(origin.x + offsetX, window.getSize().y), sf::Color::Black),
            sf::Vertex(sf::Vector2f(0, origin.y + offsetY), sf::Color::Black),
            sf::Vertex(sf::Vector2f(window.getSize().x, origin.y + offsetY), sf::Color::Black)
        };
    window.draw(axes, 2, sf::Lines);
    window.draw(&axes[2], 2, sf::Lines);
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Polar::drawPolarLabels(sf::RenderWindow& window, GraphInfo* info)  // Draw the polar labels
    {

    float scale = info->_scale;  // Get the scale
    sf::Vector2f origin = info->_origin;  // Get the origin
    float offsetX = info->_offsetX;  // Get the offset x
    float offsetY = info->_offsetY;  // Get the offset y
    const sf::Font& font = app_font();  // shared font, loaded once

    sf::Text label;
    label.setFont(font);  // Set the font of the label
    label.setCharacterSize(15);  // Set the character size of the label
    label.setFillColor(sf::Color::Black);  // Set the fill color of the label

    // Draw radius labels
    // for (float r = scale; r < window.getSize().x; r += scale)
    //     {
    //     label.setString(to_string(static_cast<int>(r / scale)));
    //     label.setPosition(origin.x + offsetX + r, origin.y + offsetY);
    //     window.draw(label);
    //     }

    // Draw angle labels
    for (int angle = 0; angle < 360; angle += 30)  // Iterate through the angles
        {
        float radian = angle * M_PI / 180;
        string piLabel;

        switch (angle)
            {
                case 0:
                case 360:
                    piLabel = "0";
                    break;
                case 30:
                    piLabel = "π/6";
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
                case 150:
                    piLabel = "5π/6";
                    break;
                case 180:
                    piLabel = "π";
                    break;
                case 210:
                    piLabel = "7π/6";
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
                case 330:
                    piLabel = "11π/6";
                    break;
                default:
                    piLabel = to_string(angle) + "°";
                    break;
            }

        wstring wpiLabel(piLabel.begin(), piLabel.end()); // wstring is a wide string which can hold UTF-16 encoded characters
        label.setString(sf::String::fromUtf8(wpiLabel.begin(), wpiLabel.end()));

        float x = origin.x + offsetX + (scale * cos(radian)) * 2.1; // Slightly offset the position to avoid overlap with the circle
        float y = origin.y + offsetY - (scale * sin(radian)) * 1.9; // Slightly offset the position to avoid overlap with the circle
        label.setPosition(x, y);
        window.draw(label);
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Polar::drawPoints(sf::RenderWindow& window, GraphInfo* info)  // Draw the points
    {
    vector<sf::Color> colors = info->_colors;  // Get the colors
    vector<vector<sf::Vector2f>> points = info->getPointsData();  // Get the points data

    for (size_t eqIndex = 0; eqIndex < points.size(); ++eqIndex)  // Iterate through the points data
        {
        for (const auto& point : points[eqIndex])  // Iterate through the points
            {
            sf::CircleShape shape(2);  // Create a circle shape
            shape.setPosition(point);  // Set the position of the shape
            shape.setFillColor(colors[eqIndex]);  // Set the fill color of the shape
            window.draw(shape);  // Draw the shape
            }
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Polar::set_info(GraphInfo* info)  // Set the information of the graph
    {
    _info = info;     // Set the information of the graph
    _coordTranslation.set_info(info);

    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Polar::drawRoseCurve(sf::RenderWindow& window, GraphInfo* info)   // Draw the rose curve
    {
    vector<vector<sf::Vector2f>> points = info->getPointsData(); // Get the points data
    for (const auto& pointSet : points)  // Iterate through the points data
        {
        for (const auto& point : pointSet)  // Iterate through the points
            {
            sf::CircleShape shape(2);  // Create a circle shape
            shape.setPosition(point);  // Set the position of the shape
            shape.setFillColor(sf::Color::Red);  // Set the fill color of the shape
            window.draw(shape); // Draw the shape
            }
        }
    }




