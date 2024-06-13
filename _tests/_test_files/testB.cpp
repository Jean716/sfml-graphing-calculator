#include "gtest/gtest.h"
#include <iostream>
using namespace std;
#include <iomanip>

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
#include "../../includes/exceptions/dividebyzero.h"

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

void printVector(const sf::Vector2f& vec)
    {
    cout << "(" << vec.x << ", " << vec.y << ")" << endl;
    }

void testTranslateMathToScreen()
    {
    cout << "Running testTranslateMathToScreen..." << endl;
    GraphInfo info;
    info._origin = sf::Vector2f(400, 300);
    info._scale = 100;
    info._offsetX = 10;
    info._offsetY = 20;

    CoordTranslation translation(&info);

    sf::Vector2f mathPoint(2, 3);
    sf::Vector2f screenPoint = translation.translate(mathPoint);

    cout << "Math Point: ";
    printVector(mathPoint);
    cout << "Screen Point: ";
    printVector(screenPoint);
    }

void testGetMathCoordsFromScreen()
    {
    cout << "Running testGetMathCoordsFromScreen..." << endl;
    GraphInfo info;
    info._origin = sf::Vector2f(400, 300);
    info._scale = 100;
    info._offsetX = 10;
    info._offsetY = 20;

    CoordTranslation translation(&info);

    sf::Vector2f screenPoint(610, -20);
    sf::Vector2f mathPoint = translation.getMathCoords(screenPoint);

    cout << "Screen Point: ";
    printVector(screenPoint);
    cout << "Math Point: ";
    printVector(mathPoint);
    }

void testPolarToCartesian()
    {
    cout << "Running testPolarToCartesian..." << endl;
    CoordTranslation translation;

    float r = 5;
    float theta = M_PI / 4; // 45 degrees
    sf::Vector2f cartesian = translation.polarToCartesian(r, theta);

    cout << "Polar Coord (r, theta): (" << r << ", " << theta << ")" << endl;
    cout << "Cartesian Coord: ";
    printVector(cartesian);
    }

void testCartesianToPolar()
    {
    cout << "Running testCartesianToPolar..." << endl;
    CoordTranslation translation;

    sf::Vector2f cartesian(3, 4);
    sf::Vector2f polar = translation.cartesianToPolar(cartesian);

    cout << "Cartesian Coord: ";
    printVector(cartesian);
    cout << "Polar Coord (r, theta): ";
    printVector(polar);
    }

void testGetPolarCoordsFromScreen()
    {
    cout << "Running testGetPolarCoordsFromScreen..." << endl;
    GraphInfo info;
    info._origin = sf::Vector2f(400, 300);
    info._scale = 100;
    info._offsetX = 10;
    info._offsetY = 20;

    CoordTranslation translation(&info);

    sf::Vector2f screenPoint(510, 180);
    sf::Vector2f polarCoords = translation.getPolarCoords(screenPoint);

    cout << "Screen Point: ";
    printVector(screenPoint);
    cout << "Polar Coord (r, theta): ";
    printVector(polarCoords);
    }

int main(int argc, char **argv)
    {
    ::testing::InitGoogleTest(&argc, argv);
    cout << "\n\n----------running testB.cpp---------\n\n" << endl;
    testTranslateMathToScreen();
    testGetMathCoordsFromScreen();
    testPolarToCartesian();
    testCartesianToPolar();
    testGetPolarCoordsFromScreen();
    return RUN_ALL_TESTS();
    }

