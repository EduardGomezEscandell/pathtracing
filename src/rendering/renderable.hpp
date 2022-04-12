#pragma once

// STD includes
#include <memory>
#include <concepts>
#include <optional>

// External library includes

// Project includes
#include "geometry/geometry.hpp"
#include "geometry/hit.hpp"
#include "rendering/material.hpp"

class Renderable
{
public:
    Renderable(Material const& material)
        : m_geometry(nullptr), m_material(material)
    { }

    template<std::derived_from<Geometry> T>
    Renderable(T const& geometry, Material const& material)
        : m_geometry(std::make_unique<T>(geometry)), m_material(material)
    { }

    template<std::derived_from<Geometry> T>
    Renderable(T && geometry, Material const& material)
        : m_geometry(std::make_unique<T>(geometry)), m_material(material)
    { }

    template<std::derived_from<Geometry> T>
    Geometry& set_geometry(T const& geometry)
    {
        m_geometry = std::make_unique<T>(geometry);
        return *m_geometry;
    }

    Geometry& get_geometry()
    {
    #ifndef DNDEBUG
        if(!m_geometry) throw std::runtime_error("Renderable has no geometry");
    #endif
        return *m_geometry;
    }

    Geometry const& get_geometry() const
    {
    #ifndef DNDEBUG
        if(!m_geometry) throw std::runtime_error("Renderable has no geometry");
    #endif
        return *m_geometry;
    }

    bool has_geometry() const noexcept { return m_geometry != nullptr; }

    std::optional<Hit> cast(LightRay const& light_ray) const
    {
        if(!m_geometry) return std::nullopt;

        return m_geometry->intersect(light_ray);
    }

    void interact(LightRay & light_ray, Hit const& hit) const
    {
        m_material.interact(light_ray, hit);
    }

protected:
    std::unique_ptr<Geometry> m_geometry;
    Material m_material;
};