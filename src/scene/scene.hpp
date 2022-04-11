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

    // Geometry
    std::vector<Renderable> & get_renderables() { return m_renderables; }
    std::vector<Renderable> const& get_renderables() const { return m_renderables; }

    // Camera
    template<typename ...Args>
    Camera& set_camera(Args const& ... args) { m_camera = Camera(args); return m_camera; }

    Camera& get_camera() { return m_camera; }
    Camera const& get_camera() const { return m_camera; }

protected:
    Camera m_camera;
    std::vector<Renderable> m_renderables;
};