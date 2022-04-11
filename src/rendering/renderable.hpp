#pragma once

// STD includes
#include <memory>
#include <concepts>

// External library includes

// Project includes
#include "geometry/geometry.hpp"
#include "geometry/hit.hpp"

class Renderable
{
public:
    template<std::derived_from<Geometry> T>
    Renderable(T const& geometry, Material const& material)
        : m_geometry(std::make_unique<T>(geometry)), m_material(material)
    { }

    template<std::derived_from<Geometry> T>
    Renderable(T && geometry, Material const& material)
        : m_geometry(std::make_unique<T>(geometry)), m_material(material)
    { }

    bool shine(LightRay& light_ray)
    {
        auto hit = m_geometry->intersect(light_ray);

        if(!hit) return false;

        m_material.interact(light_ray, *hit);
        return true;
    }

protected:
    std::unique_ptr<Geometry> m_geometry;
    Material m_material;
};