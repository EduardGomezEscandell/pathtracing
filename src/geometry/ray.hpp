#pragma once

// STD includes

// External library includes
#include <Eigen/Dense>

// Project includes

struct Ray {
    Ray(const Eigen::Vector3d& origin, const Eigen::Vector3d& direction)
        : origin(origin), direction(direction)
    {
        const double direction_norm = direction.norm();
        if(direction_norm < epsilon)
        {
            throw std::invalid_argument("Direction vector must be non-zero");
        }

        this->direction /= direction_norm;
    }

    Eigen::Vector3d origin;
    Eigen::Vector3d direction;

private:
    static constexpr double epsilon = 1e-8;
};
