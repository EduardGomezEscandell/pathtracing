#pragma once

// STD includes

// External library includes

// Project includes
#include "geometry/hit.hpp"
#include "rendering/light_ray.hpp"
#include "color.hpp"


class Material
{
public:
    Material(Color color)
        : m_color(color)
    { }

    void bounce(LightRay& ray, Hit const& hit) const
    {
        ray.source = hit.position;
        ray.direction -= 2*ray.direction.dot(hit.normal)*hit.normal,
        ray.direction.normalize();
        --ray.energy;
    };

    void tint(LightRay& ray, Hit const&) const
    {
        ray.color = m_color;
    };

protected:
    Color m_color;
};