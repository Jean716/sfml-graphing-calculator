#include "plot.h"
#include "../includes/rpn/rpn.h"
#include "graphInfo.h"
#include "constants.h"
#include "coord_translation.h"
#include  <sstream>
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

Plot::Plot(GraphInfo* info) : _info(info), _coordTranslation(info)
    {
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

void Plot::set_info(GraphInfo* info)  // set the information of the graph
    {
    cout << "Plot:: set_info is fired" << endl;
    _info = info;  // set the information of the graph
    _coordTranslation.set_info(info);  // set the information of the coordinate translation
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/

vector<vector<sf::Vector2f>> Plot::operator()(float xMin, float xMax, float increment)
    {
    cout << "================Plot::operator() is Fired================" << endl;
    if (_info->_mode == GraphInfo::CARTESIAN)  // check if the mode is cartesian
        {
        return calculateC(xMin, xMax, increment);  // call the calculateC function
        }
    else if (_info->_mode == GraphInfo::POLAR)  // check if the mode is polar
        {
        if (_info->_history.size() > 0 && _info->_history[0].find("a") != string::npos && _info->_history[0].find("b") != string::npos)
            {
            float a = _info->a;  // get the value of a
            float b = _info->b;  // get the value of b
            cout << _info->a << " " << _info->b << endl;  // print the values of a and b
            return calculateRoseCurve(0, 2 * M_PI, increment, a, b); // handle the rose curve with additional parameters
            }
        return calculateP(0, 2 * M_PI, increment);  // call the calculateP function
        }
    return {};
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/
// calculate and return all the math coordinates which is 2D vector
/*
    •	Initialization: Sets up necessary variables and vectors.
    •	Tokenization and Parsing: Converts equations into postfix expressions using the Shunting Yard algorithm.
    •	Evaluation: Uses the RPN evaluator to calculate y-values for each x-value in the specified range.
    •	Coordinate Translation: Translates mathematical coordinates to screen coordinates.
    •	Storing Results: Collects and stores screen coordinates for each equation, returning them as a 2D vector.
*/
vector<vector<sf::Vector2f>> Plot::calculateC(float xMin, float xMax, float increment)
    {
    vector<vector<sf::Vector2f>> allScreenPoints;  // 2D vector to store all screen points

    float step = (xMax - xMin) / _info->_points; // Calculate the step size

    vector<string> equations = _info->_history;  // get the equations
    vector<sf::Color> colors = _info->_colors;  // get the colors

    for (size_t eqIndex = 0; eqIndex < equations.size(); ++eqIndex)  // loop through the equations
        {
        vector<sf::Vector2f> screenPoints;  // vector to store the screen points

        // Get the postfix expression
        Queue<Token*> infix = tokenize(equations[eqIndex]);  // tokenize the equation

        // Convert Queue to vector
        vector<Token*> vec;
        while (!infix.empty())  // loop through the infix
            {
            vec.push_back(infix.pop());  // push the infix to the vector
            }

        // Convert vector back to Queue
        Queue<Token*> infixCopy;  // create a queue
        for (Token* token : vec)  // loop through the vector
            {
            infixCopy.push(token);  // push the token to the queue
            }

        ShuntingYard sy;
        // Now you can pass infixCopy to ShuntingYard::postfix
        Queue<Token*> postfix = sy.postfix(infixCopy);

        // Evaluate the RPN expression
        RPN _rpn(postfix);

        _rpn.set_input(postfix);  // set the input of the RPN

        for (int i = 0; i <= _info->_points; ++i)  // loop through the points
            {
            float x = xMin + i * step;  // Calculate the x value
            // Evaluate the RPN expression for the current x value
            float y = _rpn(x);

            cout << "Evaluating RPN with x = " << x << " Result: y = " << y << endl;

            // Translate mathematical coordinates to screen coordinates
            sf::Vector2f screenCoord = _coordTranslation(sf::Vector2f(x, y));
            cout << "Math Coord: (" << x << ", " << y << ") -> Screen Coord: (" << screenCoord.x << ", " << screenCoord.y << ")" << endl;

            screenPoints.push_back(screenCoord);  // push the screen coordinates to the vector
            }
        allScreenPoints.push_back(screenPoints);  // push the screen points to the 2D vector
        }
    return allScreenPoints;  // return the screen points
    }
//*------------------------------------------------------- DIVISION -------------------------------------------------------*/
vector<vector<sf::Vector2f>> Plot::calculateP(float thetaMin, float thetaMax, float increment)  // calculate the polar coordinates
    {
    vector<vector<sf::Vector2f>> allScreenPoints; // 2D vector to store all screen points 
    int pointsCount = _info->_points;
    float step = (thetaMax - thetaMin) / pointsCount; // Calculate the step size

    vector<string> equations = _info->_history;  // get the equations
    vector<sf::Color> colors = _info->_colors;  // get the colors

    for (size_t eqIndex = 0; eqIndex < equations.size(); ++eqIndex)  // loop through the equations
        {
        vector<sf::Vector2f> screenPoints;  // vector to store the screen points

        // Get the postfix expression
        Queue<Token*> infix = tokenize(equations[eqIndex]);  // tokenize the equation

        // Convert Queue to vector
        vector<Token*> vec;
        while (!infix.empty())
            {
            vec.push_back(infix.pop());  // push the infix to the vector
            }

        // Convert vector back to Queue
        Queue<Token*> infixCopy;
        for (Token* token : vec)
            {
            infixCopy.push(token);  // push the token to the queue
            }

        ShuntingYard sy;
        // Now you can pass infixCopy to ShuntingYard::postfix
        Queue<Token*> postfix = sy.postfix(infixCopy);

        // Evaluate the RPN expression
        RPN _rpn(postfix);  // create an RPN object
        _rpn.set_input(postfix);  // set the input of the RPN


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

            screenPoints.push_back(screenCoord); // push the screen coordinates to the vector
            }
        allScreenPoints.push_back(screenPoints); // push the screen points to the 2D vector
        }


    _info->setPointsData(allScreenPoints); // set the points data

    return allScreenPoints; // return the screen points
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
        else if (token->get_value() == "a")
            {
            Token* newToken = new Integer(_info->a);
            tokenQueue.push(newToken);
            }
        else if (token->get_value() == "b")
            {
            Token* newToken = new Integer(_info->b);
            tokenQueue.push(newToken);
            }

        else
            {
            tokenQueue.push(token);
            }
        }

    return tokenQueue;
    }

vector<vector<sf::Vector2f>> Plot::calculateRoseCurve(float thetaMin, float thetaMax, float increment, float a, float b)
    {

    vector<vector<sf::Vector2f>> allScreenPoints; // 2D vector to store all screen points 
    int pointsCount = _info->_points;
    float step = (thetaMax - thetaMin) / pointsCount; // Calculate the step size

    // Generate the expression with actual values of a and b
    string expression = "a * sin(b * theta)";
    vector<string> equations;
    if (_info->_mode == GraphInfo::POLAR)
        {
        equations.push_back(expression);
        }


    vector<sf::Color> colors = _info->_colors; // get the colors of the graph

    for (size_t eqIndex = 0; eqIndex < equations.size(); ++eqIndex) // loop through the equations
        {
        vector<sf::Vector2f> screenPoints; // vector to store the screen points

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
        for (Token* token : vec) // loop through the tokens
            {
            infixCopy.push(token); // push the token to the queue
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
            cout << "a: " << _info->a << ", b: " << _info->b << ", theta: " << theta << endl;

            // Evaluate the RPN expression for the current theta value
            float r = _rpn(theta);  // Use theta as the input variable

            cout << "Evaluating RPN with theta = " << theta << " Result: r = " << r << endl;

            // Convert polar coordinates to Cartesian coordinates
            float x = r * cos(theta);
            float y = r * sin(theta);

            // Translate mathematical coordinates to screen coordinates
            sf::Vector2f screenCoord = _coordTranslation(sf::Vector2f(x, y));
            cout << "Polar Coord: (" << r << ", " << theta << ") -> Cartesian Coord: (" << x << ", " << y << ") -> Screen Coord: (" << screenCoord.x << ", " << screenCoord.y << ")" << endl;

            screenPoints.push_back(screenCoord); // push the screen coordinates to the vector
            }
        allScreenPoints.push_back(screenPoints); // push the screen points to the 2D vector
        }

    _info->setPointsData(allScreenPoints); // set the points data

    return allScreenPoints; // return the screen points
    }