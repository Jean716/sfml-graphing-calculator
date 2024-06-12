#include "plot.h"
#include "../includes/rpn/rpn.h"
#include "graphInfo.h"
#include "constants.h"
#include "coord_translation.h"

Plot::Plot(GraphInfo* info) : _info(info), _coordTranslation(info)
    {
    }

void Plot::set_info(GraphInfo* info)
    {
    cout << "Plot:: set_info is fired" << endl;
    _info = info;
    _coordTranslation.set_info(info);
    }

vector<vector<sf::Vector2f>> Plot::operator()(float xMin, float xMax, float increment)
    {
    cout << "================Plot::operator() is Fired================" << endl;
    if (_info->getMode() == GraphInfo::CARTESIAN)
        {
        return calculateC(xMin, xMax, increment);
        }
    else if (_info->getMode() == GraphInfo::POLAR)
        {
        return calculateP(0, 2 * M_PI, increment);
        }
    return {};
    }

vector<vector<sf::Vector2f>> Plot::calculateC(float xMin, float xMax, float increment)
    {
    vector<vector<sf::Vector2f>> allScreenPoints;
    int pointsCount = _info->getPoints();
    float step = (xMax - xMin) / pointsCount; // Calculate the step size

    vector<string> equations = _info->getEquations();
    vector<sf::Color> colors = _info->getColors();

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
/*========================================================================================================================*/
vector<vector<sf::Vector2f>> Plot::calculateP(float thetaMin, float thetaMax, float increment)
    {
    vector<vector<sf::Vector2f>> allScreenPoints;
    int pointsCount = _info->getPoints();
    float step = (thetaMax - thetaMin) / pointsCount; // Calculate the step size

    vector<string> equations = _info->getEquations();
    vector<sf::Color> colors = _info->getColors();

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

    // 存储计算出的点到GraphInfo中
    _info->setPointsData(allScreenPoints);

    return allScreenPoints;
    }

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