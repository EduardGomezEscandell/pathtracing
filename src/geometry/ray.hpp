#pragma once

// STD includes

// External library includes
#include <Eigen/Dense>

// Project includes

struct Ray {
    Ray(const Eigen::Vector3d& origin, const Eigen::Vector3d& direction);

    Eigen::Vector3d origin;
    Eigen::Vector3d direction;

private:
    static constexpr double epsilon = 1e-8;
};
