// STD includes
#include <limits>

// External library includes

// Project includes
#include "multi_geometry.hpp"

std::optional<Hit> MultiGeometry::intersect(const Ray& ray) const
{
    std::optional<Hit> closest_hit = std::nullopt;

    for(auto &geom: m_geometries)
    {
        auto hit = geom->intersect(ray);
        if(!hit) continue;

        if(!closest_hit || hit->distance < closest_hit->distance)
        {
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