#pragma once

// STD includes

// External library includes
#include <doctest/doctest.h>

// Project includes
#include "geometry/ray.hpp"


TEST_CASE("Ray")
{
    Ray ray({1.0, 3.0, 7.0}, {3.0, 4.0, -5.0});

    SUBCASE("Normalization")
    {
        REQUIRE_EQ(ray.direction.norm(), doctest::Approx(1.0));
        REQUIRE_NE(ray.source.norm(), doctest::Approx(1.0));

        const double original_norm = std::sqrt(3*3 + 4*4 + 5*5);
        CHECK_EQ(ray.direction[0],  3 / original_norm);
        CHECK_EQ(ray.direction[1],  4 / original_norm);
        CHECK_EQ(ray.direction[2], -5 / original_norm);
    }
}