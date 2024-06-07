#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../includes/system.h"
#include "../../includes/graph.h"
#include "../../includes/animate.h"
#include "../../includes/sidebar.h"
#include "../../includes/graphInfo.h"
#include "../../includes/constants.h"
#include "../../includes/coord_translation.h"
#include "../../includes/plot.h"
#include "../../includes/token/token.h"
#include "../../includes/token/variable.h"
using namespace std;

bool test_stub(bool debug = false)
    {
    if (debug)
        {
        cout << "testB:: test-sub() entering test_sub" << endl;
        }
    return true;
    }

TEST(TEST_STUB, TestStub)
    {

    //EXPECT_EQ(0, <your individual test functions are called here>);

    EXPECT_EQ(1, test_stub(false));
    }


// //Function to test the tokenize method


// void test_plot_operator()
//   {
//   cout << "================Test__plot_operator()==========" << endl;
//   // create a Graphinfo object with the equation, domain, scale, and origin
//   GraphInfo info;
//   info.setEquation("sin(x)");
//   info.setDomain(sf::Vector2f(-10, 10));
//   info.setScale(50.0f);
//   info.setOrigin(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

//   // create a Plot object with the Graphinfo object
//   Plot plot(&info);

//   // call the operator() method to generate points
//   vector<sf::Vector2f> points = plot(-5, 5, 0.5f);


//   cout << "Generated Points:" << endl;
//   for (const auto& point : points)
//     {
//     cout << "Math Point: (" << point.x << ", " << point.y << "), Screen Point: (" << point.x << ", " << point.y << ")" << endl;
//     }
//   cout << "\n\n";
//   }

// void test_shunting_yard()
//   {

//   Queue<Token*> infix;
//   infix.push(new Function("sin"));
//   infix.push(new LeftParen());
//   infix.push(new Variable("x"));
//   infix.push(new Operator("+"));
//   infix.push(new Integer(1));
//   infix.push(new RightParen());

//   cout << "Infix expression: ";
//   Queue<Token*> tempInfix = infix;
//   while (!tempInfix.empty())
//     {
//     Token* t = tempInfix.pop();
//     t->print();
//     cout << " ";
//     }
//   cout << endl;

//   ShuntingYard sy;
//   Queue<Token*> postfix = sy.postfix(infix);


//   cout << "Postfix expression: ";
//   Queue<Token*> tempPostfix = postfix;
//   while (!tempPostfix.empty())
//     {
//     Token* t = tempPostfix.pop();
//     t->print();
//     cout << " ";
//     }
//   cout << endl;
//   }

int main(int argc, char **argv)
    {
    ::testing::InitGoogleTest(&argc, argv);
    cout << "\n\n----------running testB.cpp---------\n\n" << endl;
    //   test_tokenize();
    //   test_plot_operator();
    //   test_shunting_yard();
    return RUN_ALL_TESTS();
    }

