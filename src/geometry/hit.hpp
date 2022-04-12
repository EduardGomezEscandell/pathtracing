#pragma once

// STD includes

// External library includes
#include <Eigen/Dense>

// Project includes

struct Hit {
    Hit(const Eigen::Vector3d& position,
        const Eigen::Vector3d& normal,
        const double distance)
        : position(position), normal(normal), distance(distance)
    {
        assert(distance >= 0 && "Distance must be positive");
    }

    Eigen::Vector3d position;
    Eigen::Vector3d normal;
    double distance;
};