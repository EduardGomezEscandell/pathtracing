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

    std::optional<Hit> Intersect(const Ray& ray) override;

private:
    double m_radius;
    Eigen::Vector3d m_center;
};