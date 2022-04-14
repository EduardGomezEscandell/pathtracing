#pragma once

// STD includes
#include <numbers>
#include <cmath>

// External library includes

// Project includes
#include "light_physics/constexpr_math.hpp"


namespace {

    static constexpr double PI = std::numbers::pi;

    constexpr bool almost_equal(const double x, const double y)
    {
        constexpr double tolerance = 1e-12;
        return std::abs(x - y) < tolerance;
    }
}

// Testing at compile-time!

// Negatives
static_assert(almost_equal(constexpr_math::sin(-80), 0.993888653923));
static_assert(almost_equal(constexpr_math::cos(-80), -0.110387243839));

// More than 360 degrees
static_assert(almost_equal(constexpr_math::sin(1000), 0.826879540532));
static_assert(almost_equal(constexpr_math::cos(1000), 0.562379076291));

// Range 180 - 360 degrees
static_assert(almost_equal(constexpr_math::sin(3.5), -0.35078322769));
static_assert(almost_equal(constexpr_math::cos(3.5), -0.936456687291));

// Range 45 - 180 degrees
static_assert(almost_equal(constexpr_math::sin(2.7), 0.427379880234));
static_assert(almost_equal(constexpr_math::cos(2.7), -0.904072142017));

// Range 0 - 45 degrees
static_assert(almost_equal(constexpr_math::sin(0.4), 0.389418342309));
static_assert(almost_equal(constexpr_math::cos(0.4), 0.921060994003));

// Key values
static_assert(almost_equal(constexpr_math::sin(0.0), 0.0));
static_assert(almost_equal(constexpr_math::cos(0.0), 1.0));

static_assert(almost_equal(constexpr_math::sin(PI/2), 1.0));
static_assert(almost_equal(constexpr_math::cos(PI/2), 0.0));

static_assert(almost_equal(constexpr_math::sin(PI/4), 0.7071067811865476)); // Point with largest inaccuracy
static_assert(almost_equal(constexpr_math::cos(PI/4), 0.7071067811865476)); // Point with largest inaccuracy