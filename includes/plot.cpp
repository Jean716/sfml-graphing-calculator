#include "plot.h"
// #include "../includes/rpn/rpn.h"
#include "graphInfo.h"
#include "constants.h"
#include "coord_translation.h"

// #include "../includes/token/function.h"
// #include "../includes/rpn/rpn.h"
// #include "../includes/token/operator.h"
// #include "../includes/token/integer.h"
// #include "../includes/token/leftparen.h"
// #include "../includes/token/rightparen.h"
// #include "../includes/coord_translation.h"
// #include "../includes/token/token.h"
// #include "../includes/queue/MyQueue.h"
// #include "../includes/stack/MyStack.h"
// #include "../includes/token/variable.h"
// #include "../includes/token/token.h"
// #include "../includes/token/tk_string.h"
// #include "../includes/shunting_yard/shunting_yard.h"
// #include <sstream> // for istringstream
// #include <cctype>
// #include <iostream>
// using namespace std;



Plot::Plot(GraphInfo* info) : _info(info), _coordTranslation(info)
    {
    }
// // 设置 Graphinfo 对象
void Plot::set_info(GraphInfo* info)
    {
    _info = info;
    _coordTranslation = CoordTranslation(info); // 更新坐标转换
    }



// vector<sf::Vector2f> Plot::operator()(float xMin, float xMax, float increment)
//     {
//     cout << "================Plot::operator() is Fired================" << endl;
//     vector<sf::Vector2f> screenCoords;
//     // Get the postfix expression
//     Queue<Token*> infix = tokenize(_info->getEquation());

//     // Convert Queue to std::vector
//     std::vector<Token*> vec;
//     while (!infix.empty())
//         {
//         vec.push_back(infix.pop());
//         }

//     // Convert std::vector back to Queue
//     Queue<Token*> infixCopy;
//     for (Token* token : vec)
//         {
//         infixCopy.push(token);
//         }

//     ShuntingYard sy;
//     // Now you can pass infixCopy to ShuntingYard::postfix
//     Queue<Token*> postfix = sy.postfix(infixCopy);

//     // Evaluate the RPN expression
//     RPN _rpn(postfix);

//     _rpn.set_input(postfix);

//     for (float x = xMin; x <= xMax; x += increment)
//         {
//         // Evaluate the RPN expression for the current x value
//         float y = _rpn(x);
//         std::cout << "Evaluating RPN with x = " << x << " Result: y = " << y << std::endl;

//         // Translate mathematical coordinates to screen coordinates
//         sf::Vector2f screenCoord = _coordTranslation(sf::Vector2f(x, y));
//         std::cout << "Math Coord: (" << x << ", " << y << ") -> Screen Coord: (" << screenCoord.x << ", " << screenCoord.y << ")" << std::endl;

//         screenCoords.push_back(screenCoord);
//         }

//     return screenCoords;
//     }


// // convert the equation to tokens queue
// Queue<Token*> Plot::tokenize(const string& equation) const
//     {
//     cout << "================Plot::tokenize() is Fired================" << endl;
//     vector<string> tokenStrings = TK_string::split(equation);
//     Queue<Token*> tokens;

//     for (const auto& str : tokenStrings)
//         {
//         cout << "Processing token: " << str << endl; // Print the current token

//         if (isdigit(str[0]) || (str[0] == '-' && str.size() > 1 && isdigit(str[1])))
//             {
//             cout << "Recognized as Integer" << endl; // Print the type of the token
//             tokens.push(new Integer(stoi(str)));
//             }
//         else if (str == "+" || str == "-" || str == "*" || str == "/" || str == "^")
//             {
//             cout << "Recognized as Operator" << endl; // Print the type of the token
//             tokens.push(new Operator(str));
//             }
//         else if (str == "(")
//             {
//             cout << "Recognized as LeftParen" << endl; // Print the type of the token
//             tokens.push(new LeftParen());
//             }
//         else if (str == ")")
//             {
//             cout << "Recognized as RightParen" << endl; // Print the type of the token
//             tokens.push(new RightParen());
//             }
//         else if (str == "sin" || str == "cos" || str == "tan" || str == "cot")
//             {
//             cout << "Recognized as Function" << endl; // Print the type of the token
//             tokens.push(new Function(str));
//             }
//         else if (str == "x" || str == "X")
//             {
//             cout << "Recognized as Variable" << endl; // Print the type of the token
//             tokens.push(new Variable(str));
//             }
//         else
//             {
//             cout << "Unrecognized token: " << str << endl; // Print the unrecognized token
//             throw std::runtime_error("Unrecognized token: " + str);
//             }
//         }
//     cout << "Infix: ";
//     while (!tokens.empty())
//         {
//         Token* t = tokens.pop();

//         t->print();
//         std::cout << " ";
//         delete t; // delete the token to avoid memory leak
//         }

//     return tokens;
//     }
