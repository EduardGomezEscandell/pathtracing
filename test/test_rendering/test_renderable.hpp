#pragma once

// STD includes

// External library includes

// Project includes
#include "geometry/sphere.hpp"
#include "rendering/renderable.hpp"

TEST_CASE("Renderable")
{
    Renderable renderable(Sphere(0.5, {2.0, 1.0, 0.0}), Material(Colors::BLUE));

    SUBCASE("Collision")
    {
        LightRay ray({1.0, 0.0, 0.0}, {1.0, 2.0, 0.0}, Colors::BLACK);
        renderable.shine(ray);

        CHECK_EQ(ray.source[0], doctest::Approx(1.5));
        CHECK_EQ(ray.source[1], doctest::Approx(1.0));
        CHECK_EQ(ray.source[2], doctest::Approx(0.0));

        REQUIRE_EQ(ray.direction.norm(), doctest::Approx(1.0));

        Eigen::Vector3d expected_direction = {-1.0, 2.0, 0.0};
        expected_direction.normalize();

        CHECK_EQ(ray.direction[0], doctest::Approx(expected_direction[0]));
        CHECK_EQ(ray.direction[1], doctest::Approx(expected_direction[1]));
        CHECK_EQ(ray.direction[2], doctest::Approx(expected_direction[2]));

        CHECK_EQ(ray.color, Colors::BLUE);
    }

    SUBCASE("Tangential")
    {
        LightRay ray({1.5, 0.0, 0.0}, {0.0, 1.0, 0.0}, Colors::BLACK);
        renderable.shine(ray);

        CHECK_EQ(ray.source[0], 1.5);
        CHECK_EQ(ray.source[1], 1.0);
        CHECK_EQ(ray.source[2], 0.0);

        REQUIRE_EQ(ray.direction.norm(), doctest::Approx(1.0));

        Eigen::Vector3d expected_direction = {0.0, 1.0, 0.0};
        expected_direction.normalize();

        CHECK_EQ(ray.direction[0], doctest::Approx(expected_direction[0]));
        CHECK_EQ(ray.direction[1], doctest::Approx(expected_direction[1]));
        CHECK_EQ(ray.direction[2], doctest::Approx(expected_direction[2]));

        CHECK_EQ(ray.color, Colors::BLUE);
    }
}