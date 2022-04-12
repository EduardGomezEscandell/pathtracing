#pragma once

// STD includes

// External library includes

// Project includes
#include "geometry/multi_geometry.hpp"
#include "rendering/renderable.hpp"
#include "rendering/material.hpp"
#include "scene/camera.hpp"


class Scene
{
public:
    // Geometry
    std::vector<Renderable> & get_renderables() { return m_renderables; }
    std::vector<Renderable> const& get_renderables() const { return m_renderables; }

    // Camera
    template<typename ...Args>
    Camera& set_camera(Args const& ... args) { m_camera = Camera(args...); return m_camera; }

    Camera& get_camera() { return m_camera; }
    Camera const& get_camera() const { return m_camera; }

    // Snap
    template<std::size_t TWidth, std::size_t THeight>
    Image<TWidth, THeight> snap(std::size_t depth = 1)
    {
        return m_camera.snap<TWidth, THeight>(m_renderables, depth);
    }

protected:
    Camera m_camera;
    std::vector<Renderable> m_renderables;
};