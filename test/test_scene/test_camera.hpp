#pragma once

// STD includes

// External library includes
#include <Eigen/Dense>

// Project includes
#include "geometry/hit.hpp"
#include "rendering/renderable.hpp"
#include "rendering/color.hpp"
#include "scene/camera.hpp"


namespace {

struct DummyRenderable : public Renderable
{
    DummyRenderable()
        : Renderable(Sphere(1.0, {0.0,0.0,0.0}), Material(Colors::BLUE))
    { };

    std::optional<Hit> cast(LightRay const& light_ray) const override
    {
        if(light_ray.direction[0] < 0
           && light_ray.direction[1] > 0
           && light_ray.direction[2] > 0)
        {
            return Hit{{0,0,0}, {0,0,-1}, 1.0};
        }
        return std::nullopt;
    }

    void interact(LightRay & light_ray, Hit const&) const override
    {
        --light_ray.energy;
        light_ray.color = Colors::BLUE;
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
        std::vector<std::unique_ptr<Renderable>> renderables;
        renderables.emplace_back(std::make_unique<DummyRenderable>());

        const auto img = camera.snap<4,2>(renderables);

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