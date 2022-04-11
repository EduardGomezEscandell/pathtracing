#pragma once

// STD includes
#include <optional>

// External library includes
#include <Eigen/Dense>

// Project includes
#include "geometry.hpp"
#include "hit.hpp"


class Sphere : public Geometry
{
public:
    Sphere(double radius, Eigen::Vector3d center)
        : m_radius(radius), m_center(center)
    {}

    std::optional<Hit> intersect(Ray const& ray) const override;

protected:
    Eigen::Vector3d ComputeNormal(Eigen::Vector3d const& point) const;

private:
    double m_radius;
    Eigen::Vector3d m_center;
};