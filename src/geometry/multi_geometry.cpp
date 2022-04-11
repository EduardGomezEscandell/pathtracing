// STD includes
#include <limits>

// External library includes

// Project includes
#include "multi_geometry.hpp"

std::optional<Hit> MultiGeometry::intersect(const Ray& ray) const
{
    std::optional<Hit> closest_hit = std::nullopt;
    double closest_distance_squared = std::numeric_limits<double>::max();

    for(auto &geom: m_geometries)
    {
        auto hit = geom->intersect(ray);
        if(!hit) continue;

        const double d2 = hit->position.squaredNorm();
        if(d2 < closest_distance_squared)
        {
            closest_distance_squared = d2;
            closest_hit.swap(hit);
        }
    }

    return closest_hit;
}

std::unique_ptr<Geometry> MultiGeometry::pop()
{
    std::unique_ptr<Geometry> popped = std::move(m_geometries.back());
    m_geometries.pop_back();
    return popped;
}