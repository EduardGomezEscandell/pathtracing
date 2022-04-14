#pragma once

// STD includes

// External library includes

// Project includes
#include "material.hpp"


class RefractiveMaterial : public Material
{
public:
    RefractiveMaterial(Color color)
        : Material(color)
    { }

    void bounce(LightRay& ray, Hit const& hit) const
    {
        ray.source = hit.position;
        ray.direction -= 2*ray.direction.dot(hit.normal)*hit.normal,
        ray.direction.normalize();
        --ray.energy;
    };

    void tint(LightRay& ray, Hit const& hit) const
    {
        ray.color = m_color;
    };

protected:
    Color m_color;
};