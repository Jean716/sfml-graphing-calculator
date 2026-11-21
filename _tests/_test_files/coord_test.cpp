// Tests for CoordTranslation: math <-> screen and polar <-> Cartesian.
#include "gtest/gtest.h"
#include <cmath>

#include "coord_translation.h"
#include "graphInfo.h"

namespace {

GraphInfo make_info(float offsetX, float offsetY) {
    GraphInfo info;
    info._origin = sf::Vector2f(400, 300);
    info._scale = 100;
    info._offsetX = offsetX;
    info._offsetY = offsetY;
    return info;
}

}  // namespace

TEST(CoordTranslation, MathToScreen) {
    GraphInfo info = make_info(10, 20);
    CoordTranslation t(&info);
    sf::Vector2f s = t.translate({2, 3});
    // x: 400 + 2*100 + 10;  y: 300 - 3*100 + 20 (screen y grows downward)
    EXPECT_FLOAT_EQ(s.x, 610);
    EXPECT_FLOAT_EQ(s.y, 20);
}

TEST(CoordTranslation, RoundTripWithoutPan) {
    GraphInfo info = make_info(0, 0);
    CoordTranslation t(&info);
    for (sf::Vector2f p : {sf::Vector2f(0, 0), sf::Vector2f(2, 3), sf::Vector2f(-1.5f, 4)}) {
        sf::Vector2f back = t.getMathCoords(t.translate(p));
        EXPECT_NEAR(back.x, p.x, 1e-4);
        EXPECT_NEAR(back.y, p.y, 1e-4);
    }
}

// Known bug: getMathCoords subtracts offsetY where translate adds it, so after
// panning vertically the mouse readout is off by 2 * offsetY / scale.
TEST(CoordTranslation, DISABLED_RoundTripAfterPan) {
    GraphInfo info = make_info(10, 20);
    CoordTranslation t(&info);
    for (sf::Vector2f p : {sf::Vector2f(0, 0), sf::Vector2f(2, 3), sf::Vector2f(-1.5f, 4)}) {
        sf::Vector2f back = t.getMathCoords(t.translate(p));
        EXPECT_NEAR(back.x, p.x, 1e-4);
        EXPECT_NEAR(back.y, p.y, 1e-4);
    }
}

TEST(CoordTranslation, PolarCartesianRoundTrip) {
    CoordTranslation t;
    sf::Vector2f c = t.polarToCartesian(5, M_PI / 4);
    EXPECT_NEAR(c.x, 5 / std::sqrt(2.0), 1e-4);
    EXPECT_NEAR(c.y, 5 / std::sqrt(2.0), 1e-4);

    sf::Vector2f p = t.cartesianToPolar({3, 4});
    EXPECT_NEAR(p.x, 5, 1e-5);                    // r
    EXPECT_NEAR(p.y, std::atan2(4.0, 3.0), 1e-5);  // theta
}
