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
    vector<vector<sf::Vector2f>> allScreenPoints;
    int pointsCount = _info->getPoints();
    float step = (xMax - xMin) / pointsCount; // Calculate the step size

    vector<string> equations = _info->getEquations();
    vector<sf::Color> colors = _info->getColors();

    for (size_t eqIndex = 0; eqIndex < equations.size(); ++eqIndex)
        {
        vector<sf::Vector2f> screenPoints;

        // Get the postfix expression
        Queue<Token*> infix = tokenize(equations[eqIndex]); // 使用当前方程

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
        tokenQueue.push(token);
        }

    return tokenQueue;
    }





