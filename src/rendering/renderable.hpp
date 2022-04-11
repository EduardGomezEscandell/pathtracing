#pragma once

// STD includes

// External library includes

// Project includes
#include "geometry/geometry.hpp"
#include "geometry/hit.hpp"

class Renderable
{
public:
    Renderable(Geometry const& geometry, Material const& material)
        : m_geometry(geometry), m_material(material)
    { }

    Renderable(Geometry && geometry, Material const& material)
        : m_geometry(geometry), m_material(material)
    { }

    bool shine(LightRay& light_ray)
    {
        auto hit = m_geometry.intersect(light_ray);
        if(hit.empty()) {
            return false;
        }
        m_material.interact(light_ray, *hit);
        return true;
    }

protected:
    Geometry m_geometry;
    Material m_material;
};