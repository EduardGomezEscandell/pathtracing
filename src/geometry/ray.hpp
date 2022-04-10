#pragma once

// STD includes

// External library includes
#include <eigen/Dense>

// Project includes

struct Ray {
    Ray(Eigen::Vector3d origin, Eigen::Vector3d direction)
        : origin(origin), direction(direction)
    {}

    Eigen::Vector3d origin;
    Eigen::Vector3d direction;
};
