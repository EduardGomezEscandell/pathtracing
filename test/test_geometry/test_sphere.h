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
    Sphere sphere(1.0, {0.2, 0.1, 0.0});

    SUBCASE("Regular hit")
    {
        Ray ray({1.0, 0.0, 0.0}, {1.0, 2.0, 0.0});
        auto hit = sphere.Intersect(ray);
        CHECK(hit.has_value());
        CHECK(hit->position == Eigen::Vector3d{1.5, 1.0, 0.0});
    }
}