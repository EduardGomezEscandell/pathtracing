// STD includes
#include <optional>

// External library includes
#include <Eigen/Dense>

// Project includes
#include "sphere.hpp"
#include "hit.hpp"

std::optional<Hit> Sphere::intersect(const Ray& ray) const
{
    const Eigen::Vector3d oc = m_center - ray.source;
    const double oc_proj = oc.dot(ray.direction);
    const double discriminant = oc_proj * oc_proj - oc.dot(oc) + m_radius*m_radius;

    // No hit if closest point is outside sphere
    if(discriminant < 0.0)
    {
        return std::nullopt;
    }

    const double sqrt_discriminant = std::sqrt(discriminant);
    const double t1 = oc_proj - sqrt_discriminant;
    const double t2 = oc_proj + sqrt_discriminant;

    // No hit if closest point is behind ray source
    if(t1 < 0.0 && t2 < 0.0) return std::nullopt;
    if(t1 > 0.0 && t2 < 0.0) {
        const Eigen::Vector3d hitpoint = ray.source + ray.direction*t1;
        return Hit(hitpoint, ComputeNormal(hitpoint), t1);
    }
    if(t1 < 0.0 && t2 > 0.0) {
        const Eigen::Vector3d hitpoint = ray.source + ray.direction*t2;
        return Hit(hitpoint, ComputeNormal(hitpoint), t2);
    }

    // Return closest point
    const double t = std::min(t1, t2);
    const Eigen::Vector3d hitpoint = ray.source + ray.direction*t;
    return Hit(hitpoint, ComputeNormal(hitpoint), t);
}

/**
 * BEWARE! This does not check wether the point belongs to the geometry
 */
Eigen::Vector3d Sphere::ComputeNormal(const Eigen::Vector3d& point) const
{
    return (point - m_center).normalized();
}

std::unique_ptr<Geometry> Sphere::clone() const
{
    return std::make_unique<Sphere>(*this);
}