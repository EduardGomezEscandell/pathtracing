#pragma once

// STD includes
#include <numbers>

// External library includes
#include <Eigen/Dense>

// Project includes
#include "image/image.hpp"


class Camera
{
public:
    Camera(const Eigen::Vector3d& position = {0, 0, 0},
           const Eigen::Matrix3d& local_basis = Eigen::Matrix3d::Identity(),
           const double& horizontal_fov = 90);

    Image snap(
        std::vector<Renderable> const& renderables,
        std::size_t width,
        std::size_t height,
        std::size_t depth = 1) const;

protected:
    void cast(LightRay& ray, std::vector<Renderable> const& renderables) const;

    Eigen::Vector3d m_position;
    Eigen::Matrix3d m_local_basis;
    double m_fov;
};