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

// getMathCoords must undo translate() after panning in both directions.
TEST(CoordTranslation, RoundTripAfterPan) {
    GraphInfo info = make_info(10, 20);
    CoordTranslation t(&info);
    for (sf::Vector2f p : {sf::Vector2f(0, 0), sf::Vector2f(2, 3), sf::Vector2f(-1.5f, 4)}) {
        sf::Vector2f back = t.getMathCoords(t.translate(p));
        EXPECT_NEAR(back.x, p.x, 1e-4);
        EXPECT_NEAR(back.y, p.y, 1e-4);
    }
}

TEST(CoordTranslation, ScreenToMathAfterPan) {
    GraphInfo info = make_info(10, 20);
    CoordTranslation t(&info);
    // The math origin is drawn at (origin + offset) = (410, 320).
    sf::Vector2f m = t.getMathCoords({410, 320});
    EXPECT_NEAR(m.x, 0, 1e-5);
    EXPECT_NEAR(m.y, 0, 1e-5);
    m = t.getMathCoords({610, 20});  // 2 units right, 3 units up
    EXPECT_NEAR(m.x, 2, 1e-5);
    EXPECT_NEAR(m.y, 3, 1e-5);
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
