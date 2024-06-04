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
    _info = info;
    _coordTranslation.set_info(info);
    }

vector<sf::Vector2f> Plot::operator()(float xMin, float xMax, float increment)
    {
    cout << "================Plot::operator() is Fired================" << endl;
    vector<sf::Vector2f> screenCoords;
    // Get the postfix expression
    Queue<Token*> infix = tokenize(_info->getEquation());

    // Convert Queue to std::vector
    std::vector<Token*> vec;
    while (!infix.empty())
        {
        vec.push_back(infix.pop());
        }

    // Convert std::vector back to Queue
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

    for (float x = xMin; x <= xMax; x += increment)
        {
        // Evaluate the RPN expression for the current x value
        float y = _rpn(x);
        std::cout << "Evaluating RPN with x = " << x << " Result: y = " << y << std::endl;

        // Translate mathematical coordinates to screen coordinates
        sf::Vector2f screenCoord = _coordTranslation(sf::Vector2f(x, y));
        std::cout << "Math Coord: (" << x << ", " << y << ") -> Screen Coord: (" << screenCoord.x << ", " << screenCoord.y << ")" << std::endl;

        screenCoords.push_back(screenCoord);
        }

    return screenCoords;
    }



// convert the equation to tokens queue
Queue<Token*> Plot::tokenize(const string& equation) const
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


