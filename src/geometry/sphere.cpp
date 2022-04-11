// STD includes
#include <optional>

// External library includes
#include <Eigen/Dense>

// Project includes
#include "sphere.hpp"
#include "hit.hpp"

std::optional<Hit> Sphere::Intersect(const Ray& ray)
{
    const Eigen::Vector3d oc = m_center - ray.origin;
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

    // No hit if closest point is behind ray origin
    if(t1 < 0.0 && t2 < 0.0) return std::nullopt;
    if(t1 > 0.0 && t2 < 0.0) return Hit(m_center + ray.direction*t1);
    if(t1 < 0.0 && t2 > 0.0) return Hit(m_center + ray.direction*t1);

    // Return closest point
    return Hit(ray.origin + ray.direction*std::min(t1, t2));
}