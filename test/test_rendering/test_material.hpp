#pragma once

// STD includes

// External library includes

// Project includes
#include "geometry/hit.hpp"
#include "rendering/material.hpp"
#include "rendering/color.hpp"

TEST_CASE("Material")
{
    constexpr Color material_color = Colors::BLUE;
    constexpr Color ray_color = Colors::WHITE;
    Material material(material_color);

    SUBCASE("Collision")
    {
        LightRay ray({1.0, 0.0, 0.0}, {1.0, 2.0, 0.0}, ray_color);
        Hit hit({1.5, 1.0, 0.0}, {-1.0, 0.0, 0.0});
        material.interact(ray, hit);

        CHECK_EQ(ray.source[0], 1.5);
        CHECK_EQ(ray.source[1], 1.0);
        CHECK_EQ(ray.source[2], 0.0);

        REQUIRE_EQ(ray.direction.norm(), doctest::Approx(1.0));

        Eigen::Vector3d expected_direction = {-1.0, 2.0, 0.0};
        expected_direction.normalize();

        CHECK_EQ(ray.direction[0], doctest::Approx(expected_direction[0]));
        CHECK_EQ(ray.direction[1], doctest::Approx(expected_direction[1]));
        CHECK_EQ(ray.direction[2], doctest::Approx(expected_direction[2]));

        CHECK_EQ(ray.color, material_color);
    }

    SUBCASE("Tangential")
    {
        LightRay ray({1.5, 0.0, 0.0}, {0.0, 1.0, 0.0}, Colors::WHITE);
        Hit hit({1.5, 1.0, 0.0}, {-1.0, 0.0, 0.0});
        material.interact(ray, hit);

        CHECK_EQ(ray.source[0], 1.5);
        CHECK_EQ(ray.source[1], 1.0);
        CHECK_EQ(ray.source[2], 0.0);

        REQUIRE_EQ(ray.direction.norm(), doctest::Approx(1.0));

        Eigen::Vector3d expected_direction = {0.0, 1.0, 0.0};
        expected_direction.normalize();

        CHECK_EQ(ray.direction[0], doctest::Approx(expected_direction[0]));
        CHECK_EQ(ray.direction[1], doctest::Approx(expected_direction[1]));
        CHECK_EQ(ray.direction[2], doctest::Approx(expected_direction[2]));

        CHECK_EQ(ray.color, material_color);
    }
}