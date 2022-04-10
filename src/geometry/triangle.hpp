#pragma once

// STD includes
#include <array>

// External library includes
#include <eigen/Dense>

// Project includes
#include "geometry.hpp"

class Triangle : public Geometry
{
public:

private:
    std::array<Eigen::Vector3d, 3> vertices;
};