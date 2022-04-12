#pragma once

// STD includes
#include <numbers>

// External library includes
#include <Eigen/Dense>

// Project includes
#include "image/image.hpp"
#include "scene/lens.hpp"

class Camera
{
public:
    Camera(const Eigen::Vector3d& position = {0, 0, 0},
           const Eigen::Matrix3d& local_basis = Eigen::Matrix3d::Identity(),
           const double& horizontal_fov = 90) :
        m_position(position),
        m_local_basis(local_basis),
        m_fov(horizontal_fov * std::numbers::pi / 180)
    {

    }

    Image snap(
        std::vector<Renderable> const& renderables,
        std::size_t width,
        std::size_t height,
        std::size_t depth = 1) const
    {
        Image image(width, height);
        Lens lens(m_local_basis, width, height, m_fov);
        static constexpr Collocation collocation = Collocation::GAUSS_9;

        for(std::size_t row=0; row < height; ++row)
        {
            for(std::size_t col=0; col < width; ++col)
            {
                auto rays = lens.generate_rays<collocation>(row, col);

                for(auto& ray: rays) {
                    ray.source = m_position;
                    ray.energy = depth;
                    cast(ray, renderables);
                }

                image(row, col) = lens.integrate_color<collocation>(rays);
            }
        }
        return image;
    }

protected:
    void cast(LightRay& ray, std::vector<Renderable> const& renderables) const
    {
        [[maybe_unused]] static constexpr std::size_t max_iter = 10'000;
        [[maybe_unused]] std::size_t i=0;

        while(ray.energy)
        {
            assert(++i < max_iter && "Ray exceeded maximum iterations");

            std::optional<Hit> closest_hit = std::nullopt;
            Renderable const* closest_renderable = nullptr;

            for(auto const& renderable: renderables)
            {
                auto hit = renderable.cast(ray);
                if(!hit) continue;

                if(!closest_hit || hit->distance < closest_hit->distance)
                {
                    closest_hit.swap(hit);
                    closest_renderable = &renderable;
                }
            }

            if(!closest_hit) break;

            closest_renderable->interact(ray, *closest_hit);
        }
    }

    Eigen::Vector3d m_position;
    Eigen::Matrix3d m_local_basis;

    double m_fov;
};