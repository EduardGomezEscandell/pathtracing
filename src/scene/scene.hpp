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
    Scene() = default;
    
    Scene(Camera const& camera, std::vector<Renderable> const& renderables = {})
        : m_camera(camera), m_renderables(renderables)
    { }

    // Geometry
    std::vector<Renderable> & get_renderables() { return m_renderables; }
    std::vector<Renderable> const& get_renderables() const { return m_renderables; }

    // Camera
    template<typename ...Args>
    Camera& set_camera(Args const& ... args) { m_camera = Camera(args...); return m_camera; }

    Camera& get_camera() { return m_camera; }
    Camera const& get_camera() const { return m_camera; }

    // Snap
    Image snap(std::size_t width, std::size_t height, std::size_t depth = 1)
    {
        return m_camera.snap(m_renderables, width, height, depth);
    }

protected:
    Camera m_camera;
    std::vector<Renderable> m_renderables;
};