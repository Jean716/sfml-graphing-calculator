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



    EXPECT_EQ(1, test_stub(false));
    }

































































void testPolarPlot()
    {

    GraphInfo info;
    info.setMode(GraphInfo::POLAR);
    info.addEquation("2 * sin((3/2)theta)");


    Plot plot(&info);
    plot.set_info(&info);


    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Polar Coordinates Test");


    while (window.isOpen())
        {
        sf::Event event;
        while (window.pollEvent(event))
            {
            if (event.type == sf::Event::Closed)
                window.close();
            }

        window.clear(sf::Color::White);


        vector<vector<sf::Vector2f>> points = plot(0, 2 * M_PI, 0.01f);
        for (const auto& pointSet : points)
            {
            for (const auto& point : pointSet)
                {
                sf::CircleShape shape(2);
                shape.setPosition(point);
                shape.setFillColor(sf::Color::Red);
                window.draw(shape);
                }
            }

        window.display();
        }
    }

int main(int argc, char **argv)
    {
    ::testing::InitGoogleTest(&argc, argv);
    cout << "\n\n----------running testB.cpp---------\n\n" << endl;



    testPolarPlot();
    return RUN_ALL_TESTS();
    }

