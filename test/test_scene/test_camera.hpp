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

struct Quadrant : public Geometry
{
    Quadrant() : Geometry()
    { };

    std::optional<Hit> intersect(const Ray& ray) const override
    {
        if(ray.direction[0] < 0
         && ray.direction[1] > 0
         && ray.direction[2] > 0)
        {
            return Hit{ ray.direction, {0.0, 0.0, 1.0}, 1.0};
        }
        return std::nullopt;
    }

    std::unique_ptr<Geometry> clone() const override
    {
        return std::make_unique<Quadrant>();
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
        std::vector<Renderable> renderables;
        renderables.emplace_back(Quadrant{}, Colors::BLUE);

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