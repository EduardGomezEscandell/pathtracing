#pragma once

// STD includes

// External library includes
#include <Eigen/Dense>

// Project includes
#include "geometry/ray.hpp"
#include "rendering/color.hpp"


struct LightRay : public Ray
{
    LightRay()
        : Ray({0, 0, 0}, {1, 0, 0})
    { }
    
    LightRay(
        Eigen::Vector3d const& source,
        Eigen::Vector3d const& direction,
        const Color color,
        const std::size_t energy = 1)
        : Ray(source, direction),  color(color), energy(energy)
    {}

    Color color;
    std::size_t energy = 1;
};