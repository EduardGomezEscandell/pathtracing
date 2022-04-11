#pragma once

// STD includes

// External library includes
#include <doctest/doctest.h>
#include <Eigen/Dense>

// Project includes
#include "geometry/sphere.hpp"
#include "geometry/multi_geometry.hpp"
#include "geometry/ray.hpp"


TEST_CASE("Multi geometry")
{
    MultiGeometry mg;
    mg.emplace<Sphere>(0.5, Eigen::Vector3d{2.0, 1.0, 0.0});
    mg.emplace<Sphere>(3.0, Eigen::Vector3d{8.0, 4.0, 0.0});

    SUBCASE("Manipulation")
    {
        REQUIRE_EQ(mg.size(), 2);
        
        mg.pop();
        REQUIRE_EQ(mg.size(), 1);
        
        mg.push(Sphere(3.0, {8.0, 4.0, 0.0}));
        REQUIRE_EQ(mg.size(), 2);
    }

    SUBCASE("Regular hit")
    {
        Ray ray({1.0, 0.0, 0.0}, {1.0, 2.0, 0.0});
        
        auto hit = mg.intersect(ray);

        REQUIRE(hit.has_value());
        CHECK_EQ(hit->position[0], doctest::Approx(1.5));
        CHECK_EQ(hit->position[1], doctest::Approx(1.0));
        CHECK_EQ(hit->position[2], doctest::Approx(0.0));

        CHECK_EQ(hit->normal[0], doctest::Approx(-1.0));
        CHECK_EQ(hit->normal[1], doctest::Approx( 0.0));
        CHECK_EQ(hit->normal[2], doctest::Approx( 0.0));
    }
}