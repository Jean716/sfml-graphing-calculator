#include "plot.h"
#include "../includes/rpn/rpn.h"
#include "graphInfo.h"
#include "constants.h"
#include "coord_translation.h"
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

Plot::Plot(GraphInfo* info) : _info(info), _coordTranslation(info)
    {
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Plot::set_info(GraphInfo* info)
    {
    cout << "Plot:: set_info is fired" << endl;
    _info = info;
    _coordTranslation.set_info(info);
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

vector<vector<sf::Vector2f>> Plot::operator()(float xMin, float xMax, float increment)
    {
    cout << "================Plot::operator() is Fired================" << endl;
    if (_info->_mode == GraphInfo::CARTESIAN)
        {
        return calculateC(xMin, xMax, increment);
        }
    else if (_info->_mode == GraphInfo::POLAR)
        {
        return calculateP(0, 2 * M_PI, increment);
        }
    return {};
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/
// calculate and return all the math coordinates which is 2D vector

vector<vector<sf::Vector2f>> Plot::calculateC(float xMin, float xMax, float increment)
    {
    vector<vector<sf::Vector2f>> allScreenPoints;

    float step = (xMax - xMin) / _info->_points; // Calculate the step size

    vector<string> equations = _info->_history;
    vector<sf::Color> colors = _info->_colors;

    for (size_t eqIndex = 0; eqIndex < equations.size(); ++eqIndex)
        {
        vector<sf::Vector2f> screenPoints;

        // Get the postfix expression
        Queue<Token*> infix = tokenize(equations[eqIndex]);

        // Convert Queue to vector
        vector<Token*> vec;
        while (!infix.empty())
            {
            vec.push_back(infix.pop());
            }

        // Convert vector back to Queue
        Queue<Token*> infixCopy;
        for (Token* token : vec)
            {
            infixCopy.push(token);
            }

        ShuntingYard sy;
        // Now you can pass infixCopy to ShuntingYard::postfix
        Queue<Token*> postfix = sy.postfix(infixCopy);

        // Evaluate the RPN expression
        RPN _rpn(postfix);

        _rpn.set_input(postfix);

        for (int i = 0; i <= _info->_points; ++i)
            {
            float x = xMin + i * step;
            // Evaluate the RPN expression for the current x value
            float y = _rpn(x);

            cout << "Evaluating RPN with x = " << x << " Result: y = " << y << endl;

            // Translate mathematical coordinates to screen coordinates
            sf::Vector2f screenCoord = _coordTranslation(sf::Vector2f(x, y));
            cout << "Math Coord: (" << x << ", " << y << ") -> Screen Coord: (" << screenCoord.x << ", " << screenCoord.y << ")" << endl;

            screenPoints.push_back(screenCoord);
            }
        allScreenPoints.push_back(screenPoints);
        }
    return allScreenPoints;
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/
vector<vector<sf::Vector2f>> Plot::calculateP(float thetaMin, float thetaMax, float increment)
    {
    vector<vector<sf::Vector2f>> allScreenPoints; // 2D vector to store all screen points 
    int pointsCount = _info->_points;
    float step = (thetaMax - thetaMin) / pointsCount; // Calculate the step size

    vector<string> equations = _info->_history;
    vector<sf::Color> colors = _info->_colors;

    for (size_t eqIndex = 0; eqIndex < equations.size(); ++eqIndex)
        {
        vector<sf::Vector2f> screenPoints;

        // Get the postfix expression
        Queue<Token*> infix = tokenize(equations[eqIndex]);

        // Convert Queue to vector
        vector<Token*> vec;
        while (!infix.empty())
            {
            vec.push_back(infix.pop());
            }

        // Convert vector back to Queue
        Queue<Token*> infixCopy;
        for (Token* token : vec)
            {
            infixCopy.push(token);
            }

        ShuntingYard sy;
        // Now you can pass infixCopy to ShuntingYard::postfix
        Queue<Token*> postfix = sy.postfix(infixCopy);

        // Evaluate the RPN expression
        RPN _rpn(postfix);

        _rpn.set_input(postfix);

        for (int i = 0; i <= pointsCount; ++i)
            {
            float theta = thetaMin + i * step;
            // Evaluate the RPN expression for the current theta value
            float r = _rpn(theta);  // Use theta as the input variable

            cout << "Evaluating RPN with theta = " << theta << " Result: r = " << r << endl;

            // Convert polar coordinates to Cartesian coordinates
            float x = r * cos(theta);
            float y = r * sin(theta);

            // Translate mathematical coordinates to screen coordinates
            sf::Vector2f screenCoord = _coordTranslation(sf::Vector2f(x, y));
            cout << "Polar Coord: (" << r << ", " << theta << ") -> Cartesian Coord: (" << x << ", " << y << ") -> Screen Coord: (" << screenCoord.x << ", " << screenCoord.y << ")" << endl;

            screenPoints.push_back(screenCoord);
            }
        allScreenPoints.push_back(screenPoints);
        }


    _info->setPointsData(allScreenPoints);

    return allScreenPoints;
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/
// convert the equation to tokens queue
Queue<Token*> Plot::tokenize(const string & equation) const
    {
    TK_string tk;
    vector<Token*> tokens = tk.split(equation);
    Queue<Token*> tokenQueue;

    cout << "Tokenizing equation: " << equation << endl;
    for (Token* token : tokens)
        {
        cout << "Token: " << token->get_value() << endl;
        if (token->get_value() == "theta")
            {
            Token* newToken = new Variable("x");
            tokenQueue.push(newToken);
            }

        else
            {
            tokenQueue.push(token);
            }
        }

    return tokenQueue;
    }