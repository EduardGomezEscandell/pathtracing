#pragma once

// STD includes

// External library includes
#include <Eigen/Dense>

// Project includes
#include "rendering/renderable.hpp"
#include "rendering/color.hpp"
#include "scene/camera.hpp"

namespace {

struct DummyRenderable : public Renderable
{
    DummyRenderable()
        : Renderable(Sphere(1.0, {0.0,0.0,0.0}), Material(Colors::BLUE))
    { };

    bool shine(LightRay& light_ray) const override
    {
        if(light_ray.direction[0] < 0
           && light_ray.direction[1] > 0
           && light_ray.direction[2] > 0)
        {
            --light_ray.energy;
            light_ray.color = Colors::BLUE;
            return true;
        }
        return false;
    }
};

} // namespace

TEST_CASE("Camera")
{
    Eigen::Vector3d location;
    Eigen::Matrix3d camera_basis = Eigen::Matrix3d::Identity();

    Camera camera(location, camera_basis);

    SUBCASE("Upper left quadrant")
    {
        DummyRenderable renderable;
        const auto img = camera.snap<4,2>(renderable);

        REQUIRE(img.width == 4);
        REQUIRE(img.height == 2);

        CHECK_EQ(img(0,0), Colors::BLUE);
        CHECK_EQ(img(0,1), Colors::BLUE);
        CHECK_EQ(img(0,2), Colors::BLACK);
        CHECK_EQ(img(0,3), Colors::BLACK);

        CHECK_EQ(img(1,0), Colors::BLACK);
        CHECK_EQ(img(1,1), Colors::BLACK);
        CHECK_EQ(img(1,2), Colors::BLACK);
        CHECK_EQ(img(1,3), Colors::BLACK);
    }
}