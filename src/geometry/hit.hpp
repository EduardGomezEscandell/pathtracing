#pragma once

// STD includes

// External library includes
#include <Eigen/Dense>

// Project includes

struct Hit {
    Hit(const Eigen::Vector3d& position)
        : position(position)
    { }

    Eigen::Vector3d position;
};