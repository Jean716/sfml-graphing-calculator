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
void Graph::set_info(GraphInfo* info)  // Set the information of the graph
    {
    _info = info;  // Set the information of the graph
    _plot.set_info(info);  // Set the information of the plot object
    _coordTranslation.set_info(info);  // Set the information of the coordinate translation object
    _polar.set_info(info);  // Set the information of the polar object
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Graph::update(GraphInfo* info) // This function will be used to update the graph
    {
    set_info(info);
    generatePoints();
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Graph::draw(sf::RenderWindow& window) // This function will be used to draw the graph
    {
    if (_info->_mode == GraphInfo::CARTESIAN) // If the mode is Cartesian
        {
        drawCartesian(window); // call the drawCartesian function to draw the Cartesian graph
        }
    else if (_info->_mode == GraphInfo::POLAR) // If the mode is Polar
        {
        _polar.draw(window, _info); // call the draw function of the Polar object to draw the Polar graph

        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Graph::drawCartesian(sf::RenderWindow& window) // Draw the Cartesian graph
    {
    drawAxes(window);  // Draw the axes for the Cartesian graph
    drawTicksAndLabels(window); // Draw ticks and labels for the Cartesian graph
    drawGraphPoints(window); // Draw the graph points
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Graph::drawAxes(sf::RenderWindow& window) // Draw the axes for the Cartesian graph
    {
    float scale = _info->_scale; // Get the scale
    sf::Vector2f origin = _info->_origin; // Get the origin
    float offsetX = _info->_offsetX; // Get the offset x
    float offsetY = _info->_offsetY; // Get the offset y

    sf::Vertex xAxis[] = {
        sf::Vertex(sf::Vector2f(0, origin.y + offsetY), sf::Color::Black), // Create a vertex for the x-axis
        sf::Vertex(sf::Vector2f(window.getSize().x, origin.y + offsetY), sf::Color::Black) // Create a vertex for the x-axis
        };
    window.draw(xAxis, 2, sf::Lines);

    sf::Vertex yAxis[] = {
        sf::Vertex(sf::Vector2f(origin.x + offsetX, 0), sf::Color::Black), // Create a vertex for the y-axis
        sf::Vertex(sf::Vector2f(origin.x + offsetX, window.getSize().y), sf::Color::Black)   // Create a vertex for the y-axis
        };
    window.draw(yAxis, 2, sf::Lines);
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Graph::drawTicksAndLabels(sf::RenderWindow& window) // Draw ticks and labels for the Cartesian graph
    {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        {
        cerr << "Error loading font" << endl; // If the font is not loaded, print an error message
        }

    float scale = _info->_scale; // Get the scale
    sf::Vector2f origin = _info->_origin; // Get the origin
    float offsetX = _info->_offsetX; // Get the offset x
    float offsetY = _info->_offsetY; // Get the offset y

    sf::Text originLabel; // Create a text object for the origin
    originLabel.setFont(font); // Set the font of the origin label
    originLabel.setCharacterSize(15); // Set the character size of the origin label
    originLabel.setFillColor(sf::Color::Black); // Set the fill color of the origin label
    originLabel.setString("0"); // Set the string of the origin label
    originLabel.setPosition(origin.x + offsetX + 5, origin.y + offsetY + 5); // Set the position of the origin label
    window.draw(originLabel); // Draw the origin label

    for (float graphX = 0; graphX * scale < window.getSize().x / 2; ++graphX) // Loop through the x-axis
        {
        if (graphX != 0)
            {
            drawTickAndLabel(window, font, graphX, scale, origin, offsetX, offsetY); // Call the drawTickAndLabel function to draw the tick and label
            }
        }

    for (float graphY = 0; graphY * scale < window.getSize().y / 2; ++graphY) // Loop through the y-axis
        {
        if (graphY != 0)
            {
            drawTickAndLabel(window, font, graphY, scale, origin, offsetX, offsetY, true); // Call the drawTickAndLabel function to draw the tick and label
            }
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/
/**==================================================================================
 * 	1.	Calculate Screen Position and Tick Lines:
    •	Determine if it is drawing Y-axis or X-axis ticks based on isYAxis.
    •	Use the origin, scale, and offsets to calculate the screen position of the tick.
    •	Create two vertices to represent the tick line and set their color to black.
    2.	Draw the Tick Lines:
    •	Use window.draw to draw the tick lines.
    3.	Draw the Labels:
    •	Create an sf::Text object for displaying the label.
    •	Set the font, character size, and color of the label.
    •	Set the string content of the label based on graphValue.
    •	Position the label based on whether it is the Y-axis or X-axis.
    •	Use window.draw to draw the label.
    4.	Handle Negative Tick Lines and Labels:
    •	For the X-axis (!isYAxis), handle the negative tick lines and labels.
    •	Recalculate the screen position and tick line position.
    •	Set the label string to the negative value and draw them.
 *
 *=================================================================================**/
void Graph::drawTickAndLabel(sf::RenderWindow& window, const sf::Font& font, float graphValue, float scale, const sf::Vector2f& origin, float offsetX, float offsetY, bool isYAxis)
    {
    sf::Vector2f screenPos;
    sf::Vertex tick[2];

    if (isYAxis)
        {
        screenPos = sf::Vector2f(origin.x + offsetX, origin.y - graphValue * scale + offsetY); // Set the screen position
        tick[0] = sf::Vertex(sf::Vector2f(origin.x + offsetX - 5, screenPos.y), sf::Color::Black); // Set the first vertex of the tick
        tick[1] = sf::Vertex(sf::Vector2f(origin.x + offsetX + 5, screenPos.y), sf::Color::Black);
        }
    else
        {
        screenPos = sf::Vector2f(origin.x + graphValue * scale + offsetX, origin.y + offsetY); // Set the screen position
        tick[0] = sf::Vertex(sf::Vector2f(screenPos.x, origin.y + offsetY - 5), sf::Color::Black); // Set the first vertex of the tick
        tick[1] = sf::Vertex(sf::Vector2f(screenPos.x, origin.y + offsetY + 5), sf::Color::Black);
        }

    window.draw(tick, 2, sf::Lines); // Draw the tick   

    sf::Text label;   // Create a text object for the label
    label.setFont(font);   // Set the font of the label
    label.setCharacterSize(15);    // Set the character size of the label
    label.setFillColor(sf::Color::Black);     // Set the fill color of the label
    label.setString(to_string(static_cast<int>(graphValue)));

    if (isYAxis)
        {
        label.setPosition(origin.x + offsetX + 10, screenPos.y);  // Set the position of the label
        }
    else
        {
        label.setPosition(screenPos.x, origin.y + offsetY + 10);  //  Set the position of the label
        }

    window.draw(label);

    if (!isYAxis)  // If the axis is not y-axis
        {
        screenPos = sf::Vector2f(origin.x - graphValue * scale + offsetX, origin.y + offsetY);  // Set the screen position
        tick[0].position = sf::Vector2f(screenPos.x, origin.y + offsetY - 5);  // Set the first vertex of the tick
        tick[1].position = sf::Vector2f(screenPos.x, origin.y + offsetY + 5); //  Set the second vertex of the tick
        window.draw(tick, 2, sf::Lines); // Draw the tick

        label.setString("-" + to_string(static_cast<int>(graphValue))); // Set the string of the label
        label.setPosition(screenPos.x, origin.y + offsetY + 10); // Set the position of the label
        window.draw(label); // Draw the label
        }
    else
        {
        screenPos = sf::Vector2f(origin.x + offsetX, origin.y + graphValue * scale + offsetY); // Set the screen position
        tick[0].position = sf::Vector2f(origin.x + offsetX - 5, screenPos.y); // Set the first vertex of the tick
        tick[1].position = sf::Vector2f(origin.x + offsetX + 5, screenPos.y);   // Set the second vertex of the tick
        window.draw(tick, 2, sf::Lines); // Draw the tick

        label.setString("-" + to_string(static_cast<int>(graphValue))); // Set the string of the label
        label.setPosition(origin.x + offsetX + 10, screenPos.y); // Set the position of the label
        window.draw(label); // Draw the label
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Graph::drawGraphPoints(sf::RenderWindow& window) // Draw the graph points
    {
    vector<sf::Color> colors = _info->_colors; // Get the colors
    for (size_t eqIndex = 0; eqIndex < _points.size(); ++eqIndex) // Loop through the equations
        {
        for (const auto& point : _points[eqIndex]) // Loop through the points
            {
            sf::CircleShape shape(2); // Create a circle shape
            shape.setPosition(point); // Set the position of the shape
            if (_info->_currentFunctionIndex == eqIndex) // If the current function index is equal to the equation index
                {
                shape.setFillColor(sf::Color::Red); // Set the fill color of the shape
                shape.setRadius(2);  // Set the radius of the shape
                }
            else
                {
                shape.setFillColor(colors[eqIndex]); // Set the fill color of the shape
                }
            window.draw(shape); // Draw the shape
            }
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Graph::generatePoints() // Call the plot object to generate the points
    {
    if (_info) // If the info is not null
        {
        _points = _plot(_info->_domain.x, _info->_domain.y, 0.1f); // Generate the points
        }
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Graph::drawDomainAndCoordinate(sf::RenderWindow& window) // Draw the domain and coordinate
    {
    sf::Font font; // Create a font object
    if (!font.loadFromFile("arial.ttf")) // If the font is not loaded
        {
        cerr << "Error loading font" << endl; // Print an error message
        }

    sf::Text domainText; // Create a text object for the domain
    domainText.setFont(font); // Set the font of the domain text
    domainText.setCharacterSize(15); // Set the character size of the domain text
    domainText.setFillColor(sf::Color::Black); // Set the fill color of the domain text

    sf::Text coordinateText; // Create a text object for the coordinate
    coordinateText.setFont(font); // Set the font of the coordinate text
    coordinateText.setCharacterSize(15); // Set the character size of the coordinate text
    coordinateText.setFillColor(sf::Color::Black); // Set the fill color of the coordinate text

    stringstream domainStream; // Create a string stream for the domain
    stringstream coordinateStream; // Create a string stream for the coordinate

    if (_info->_mode == GraphInfo::CARTESIAN) // If the mode is Cartesian
        {
        domainStream << "Domain: [" << _info->_domain.x << ", " << _info->_domain.y << "]"; // Set the domain stream
        coordinateStream << "Cartesian Coordinate: (" << _info->_origin.x << ", " << _info->_origin.y << ")";   // Set the coordinate stream
        }
    else if (_info->_mode == GraphInfo::POLAR) // If the mode is Polar
        {
        domainStream << "Domain: [0, 2π]"; // Set the domain stream
        coordinateStream << "Polar Coordinate: (r, θ)"; // Set the coordinate stream
        }

    domainText.setString(domainStream.str()); // Set the string of the domain text
    domainText.setPosition(10, 10); // Set the position of the domain text
    window.draw(domainText); // Draw the domain text

    coordinateText.setString(coordinateStream.str()); // Set the string of the coordinate text
    coordinateText.setPosition(10, 30); // Set the position of the coordinate text
    window.draw(coordinateText); // Draw the coordinate text
    }

//*------------------------------------------------------- DIVISION -------------------------------------------------------*/
void Graph::drawGrid(sf::RenderWindow & window) // Draw the grid
    {
    sf::VertexArray lines(sf::Lines); // Create a vertex array for the lines

    const float step = _info->_scale; // Get the step
    const sf::Color gridColor(200, 200, 200); // Set the grid color

    sf::Vector2f origin = _info->_origin; // Get the origin
    float offsetX = _info->_offsetX;     // Get the offset x
    float offsetY = _info->_offsetY;   // Get the offset y
    float scale = _info->_scale;   // Get the scale


    for (float x = origin.x + offsetX; x < WORK_PANEL; x += step) // Loop through the x-axis
        {
        lines.append(sf::Vertex(sf::Vector2f(x, 0), gridColor)); // Append a vertex to the lines
        lines.append(sf::Vertex(sf::Vector2f(x, SCREEN_HEIGHT), gridColor)); // Append a vertex to the lines
        }
    for (float x = origin.x + offsetX; x > 0; x -= step) // Loop through the x-axis
        {
        lines.append(sf::Vertex(sf::Vector2f(x, 0), gridColor)); // Append a vertex to the lines
        lines.append(sf::Vertex(sf::Vector2f(x, SCREEN_HEIGHT), gridColor));    // Append a vertex to the lines
        }


    for (float y = origin.y + offsetY; y < SCREEN_HEIGHT; y += step)    // Loop through the y-axis
        {
        lines.append(sf::Vertex(sf::Vector2f(0, y), gridColor)); // Append a vertex to the lines
        lines.append(sf::Vertex(sf::Vector2f(WORK_PANEL, y), gridColor)); // Append a vertex to the lines
        }
    for (float y = origin.y + offsetY; y > 0; y -= step) // Loop through the y-axis
        {
        lines.append(sf::Vertex(sf::Vector2f(0, y), gridColor)); // Append a vertex to the lines
        lines.append(sf::Vertex(sf::Vector2f(WORK_PANEL, y), gridColor)); // Append a vertex to the lines
        }

    window.draw(lines); // Draw the lines
    }



