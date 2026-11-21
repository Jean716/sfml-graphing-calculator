// Tests for Plot: sampling the domain and skipping undefined points.
#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "graphInfo.h"
#include "plot.h"
using namespace std;

namespace {

// Plot the given equations on the default Cartesian domain [-5, 5]
// (1000 steps, 1001 samples; the sample at index 500 is exactly x = 0).
vector<vector<sf::Vector2f>> plot(const vector<string>& equations) {
    GraphInfo info;
    info._history = equations;
    info._colors = vector<sf::Color>(equations.size(), sf::Color::Black);
    Plot p(&info);
    streambuf* out = cout.rdbuf(nullptr);  // silence the engine trace
    auto points = p(info._domain.x, info._domain.y, 0.1f);
    cout.rdbuf(out);
    return points;
}

bool all_finite(const vector<sf::Vector2f>& pts) {
    for (const auto& q : pts)
        if (!std::isfinite(q.x) || !std::isfinite(q.y)) return false;
    return true;
}

}  // namespace

TEST(Plot, SamplesEveryPointWhenDefined) {
    auto pts = plot({"x^2"});
    ASSERT_EQ(pts.size(), 1u);
    EXPECT_EQ(pts[0].size(), 1001u);
}

TEST(Plot, SkipsOnlyThePoleOfOneOverX) {
    auto pts = plot({"1/x"});
    ASSERT_EQ(pts.size(), 1u);
    EXPECT_EQ(pts[0].size(), 1000u);  // only x = 0 is dropped
    EXPECT_TRUE(all_finite(pts[0]));
}

TEST(Plot, SkipsWhereFunctionIsUndefined) {
    // sqrt and log are undefined for x < 0 (log(0) = -inf); 500 samples are negative.
    auto pts = plot({"sqrt(x)", "log(x)"});
    ASSERT_EQ(pts.size(), 2u);
    EXPECT_EQ(pts[0].size(), 501u);  // x = 0 .. 5
    EXPECT_EQ(pts[1].size(), 500u);  // x > 0 only
    EXPECT_TRUE(all_finite(pts[0]));
    EXPECT_TRUE(all_finite(pts[1]));
}

TEST(Plot, OneUndefinedFunctionDoesNotHideOthers) {
    auto pts = plot({"1/x", "sin(x)"});
    ASSERT_EQ(pts.size(), 2u);
    EXPECT_EQ(pts[1].size(), 1001u);
}
