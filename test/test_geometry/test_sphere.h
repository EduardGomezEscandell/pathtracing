#pragma once

// STD includes

// External library includes
#include <doctest/doctest.h>

// Project includes
#include "geometry/sphere.hpp"
#include "geometry/hit.hpp"
#include "geometry/ray.hpp"


TEST_CASE("Sphere")
{
    Sphere sphere(0.5, {2.0, 1.0, 0.0});

    SUBCASE("Regular hit")
    {
        Ray ray({1.0, 0.0, 0.0}, {1.0, 2.0, 0.0});
        auto hit = sphere.Intersect(ray);
        REQUIRE(hit.has_value());
        CHECK_EQ(hit->position[0], doctest::Approx(1.5));
        CHECK_EQ(hit->position[1], doctest::Approx(1.0));
        CHECK_EQ(hit->position[2], doctest::Approx(0.0));

        CHECK_EQ(hit->normal[0], doctest::Approx(-1.0));
        CHECK_EQ(hit->normal[1], doctest::Approx( 0.0));
        CHECK_EQ(hit->normal[2], doctest::Approx( 0.0));
    }
}