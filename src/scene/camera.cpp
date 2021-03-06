// STD includes
#include <numbers>
#include <stack>

// External library includes
#include <Eigen/Dense>

// Project includes
#include "rendering/renderable.hpp"
#include "scene/camera.hpp"
#include "light_physics/lens.hpp"
#include "image/image.hpp"

Camera::Camera(
        const double& horizontal_fov,
        const Eigen::Vector3d& position,
        const Eigen::Matrix3d& local_basis) :
    m_position(position),
    m_local_basis(local_basis),
    m_fov(horizontal_fov * std::numbers::pi / 180)
{

}

Image Camera::snap(
    std::vector<Renderable> const& renderables,
    std::size_t width,
    std::size_t height,
    std::size_t depth) const
{
    Image image(width, height);
    Lens<Collocation::GAUSS_3> lens(m_local_basis, width, height, m_fov);

    for(std::size_t row=0; row < height; ++row)
    {
        for(std::size_t col=0; col < width; ++col)
        {
            auto rays = lens.generate_rays(row, col);

            for(auto& ray: rays) {
                ray.source = m_position;
                ray.energy = depth;
                cast(ray, renderables);
            }

            image(row, col) = lens.integrate_color(rays);
        }
    }
    return image;
}

void Camera::cast(LightRay& ray, std::vector<Renderable> const& renderables) const
{
    [[maybe_unused]] static constexpr std::size_t max_iter = 10'000;
    [[maybe_unused]] std::size_t i=0;

    using HitDatum = std::pair<Hit, Renderable const&>;
    std::stack<HitDatum, std::vector<HitDatum>> hit_reccord;

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

        closest_renderable->bounce(ray, *closest_hit);
        hit_reccord.emplace(*closest_hit, *closest_renderable);
    }

    while(!hit_reccord.empty())
    {
        Hit const& hit = hit_reccord.top().first;
        Renderable const& renderable = hit_reccord.top().second;

        renderable.tint(ray, hit);

        hit_reccord.pop();
    }
}