// #include "polar.h"
// #include <cmath>
// #include <sstream>

// Polar::Polar() {}

// void Polar::draw(sf::RenderWindow& window, GraphInfo* info)
//     {
//     drawPolarGrid(window, info);
//     drawPolarLabels(window, info);
//     }

// void Polar::drawPolarGrid(sf::RenderWindow& window, GraphInfo* info)
//     {
//     float scale = info->getScale();
//     sf::Vector2f origin = info->getOrigin();
//     float offsetX = info->getOffsetX();
//     float offsetY = info->getOffsetY();

//     sf::CircleShape circle;
//     circle.setOutlineColor(sf::Color::Black);
//     circle.setOutlineThickness(1);
//     circle.setFillColor(sf::Color::Transparent);

//     for (float r = scale; r < window.getSize().x; r += scale)
//         {
//         circle.setRadius(r);
//         circle.setOrigin(r, r);
//         circle.setPosition(origin.x + offsetX, origin.y + offsetY);
//         window.draw(circle);
//         }

//     sf::Vertex line[] =
//         {
//             sf::Vertex(sf::Vector2f(origin.x + offsetX, 0), sf::Color::Black),
//             sf::Vertex(sf::Vector2f(origin.x + offsetX, window.getSize().y), sf::Color::Black),
//             sf::Vertex(sf::Vector2f(0, origin.y + offsetY), sf::Color::Black),
//             sf::Vertex(sf::Vector2f(window.getSize().x, origin.y + offsetY), sf::Color::Black)
//         };
//     window.draw(line, 2, sf::Lines);
//     window.draw(&line[2], 2, sf::Lines);
//     }

// void Polar::drawPolarLabels(sf::RenderWindow& window, GraphInfo* info)
//     {
//     float scale = info->getScale();
//     sf::Vector2f origin = info->getOrigin();
//     float offsetX = info->getOffsetX();
//     float offsetY = info->getOffsetY();
//     sf::Font font;

//     if (!font.loadFromFile("arial.ttf"))
//         {
//         // handle error
//         }

//     sf::Text label;
//     label.setFont(font);
//     label.setCharacterSize(15);
//     label.setFillColor(sf::Color::Black);

//     for (float r = scale; r < window.getSize().x; r += scale)
//         {
//         label.setString(std::to_string(static_cast<int>(r / scale)));
//         label.setPosition(origin.x + offsetX + r, origin.y + offsetY);
//         window.draw(label);
//         }

//     for (int angle = 0; angle < 360; angle += 30)
//         {
//         std::ostringstream ss;
//         ss << angle << "°";
//         label.setString(ss.str());
//         float radian = angle * M_PI / 180;
//         float x = origin.x + offsetX + 100 * cos(radian);
//         float y = origin.y + offsetY - 100 * sin(radian);
//         label.setPosition(x, y);
//         window.draw(label);
//         }
//     }