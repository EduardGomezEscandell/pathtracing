#pragma once

// STD includes

// External library includes
#include <Eigen/Dense>

// Project includes

struct Hit {
    Hit(const Eigen::Vector3d& position, const Eigen::Vector3d& normal)
        : position(position), normal(normal)
    { }

    Eigen::Vector3d position;
    Eigen::Vector3d normal;
};