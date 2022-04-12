#pragma once

// STD includes
#include <numbers>

// External library includes
#include <Eigen/Dense>


// Project includes

template<std::size_t TWidth, std::size_t THeight>
struct Image {
    static constexpr std::size_t width = TWidth;
    static constexpr std::size_t height = THeight;

    std::array<std::array<Color, width>, height> pixels;

    constexpr Color& operator()(std::size_t row, std::size_t col)
    {
    #ifndef NDEBUG
        if(row > height) throw std::invalid_argument("Row index out of bounds");
        if(col > width) throw std::invalid_argument("Column index out of bounds");
    #endif
        return pixels[row][col];
    }

    constexpr Color const& operator()(std::size_t row, std::size_t col) const
    {
    #ifndef NDEBUG
        if(row > height) throw std::invalid_argument("Row index out of bounds");
        if(col > width) throw std::invalid_argument("Column index out of bounds");
    #endif
        return pixels[row][col];
    }
};


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

    template<std::size_t TWidth = 1920, std::size_t THeight = 1080>
    Image<TWidth, THeight> snap(std::vector<std::unique_ptr<Renderable>> const& renderables, std::size_t depth = 1)
    {
        Image<TWidth, THeight> image;

        const double aspect_ratio = THeight / static_cast<double>(TWidth);
        const double hfov = m_fov * 0.5;
        const double vfov = hfov * aspect_ratio;

        for(std::size_t row=0; row < THeight; ++row)
        {
            for(std::size_t col=0; col < TWidth; ++col)
            {
                std::vector<LightRay> rays = generate_rays<TWidth, THeight>(row, col, hfov, vfov, depth);
                for(auto& ray: rays) {
                    cast(ray, renderables);
                }
                image(row, col) = reduce_color(rays);

            }
        }
        return image;
    }

protected:
    template<std::size_t TWidth = 1920, std::size_t THeight = 1080>
    std::vector<LightRay> generate_rays(
        const std::size_t row,
        const std::size_t col,
        const double hfov,
        const double vfov,
        const std::size_t energy) const
    {
        const double xi  = (col + 0.5 - 0.5*TWidth) / static_cast<double>(TWidth);
        const double eta = (0.5*THeight - row - 0.5) / static_cast<double>(THeight);

        Eigen::Vector3d local_direction {
            std::tan(hfov * xi),
            std::tan(vfov * eta),
            1
        };
        local_direction.normalize();

        Eigen::Vector3d direction = m_local_basis * local_direction;

        return {LightRay(m_position, direction, Colors::BLACK, energy)};
    }

    void cast(LightRay& ray, std::vector<std::unique_ptr<Renderable>> const& renderables) const
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
                auto hit = renderable->cast(ray);
                if(!hit) continue;

                if(!closest_hit || hit->distance < closest_hit->distance)
                {
                    closest_hit.swap(hit);
                    closest_renderable = renderable.get();
                }
            }

            if(!closest_hit) break;

            closest_renderable->interact(ray, *closest_hit);
        }
    }

    Color reduce_color(std::vector<LightRay> const& rays)
    {
        unsigned int acc_red   = 0;
        unsigned int acc_green = 0;
        unsigned int acc_blue  = 0;
        unsigned int acc_alpha = 0;

        for(auto& ray: rays)
        {
            acc_red += ray.color.r;
            acc_green += ray.color.g;
            acc_blue += ray.color.b;
            acc_alpha += ray.color.a;
        }

        const auto avg_red   = static_cast<Color::channel>(acc_red   / rays.size());
        const auto avg_green = static_cast<Color::channel>(acc_green / rays.size());
        const auto avg_blue  = static_cast<Color::channel>(acc_blue  / rays.size());
        const auto avg_alpha = static_cast<Color::channel>(acc_alpha / rays.size());

        return {avg_red, avg_green, avg_blue, avg_alpha};
    }

    Eigen::Vector3d m_position;
    Eigen::Matrix3d m_local_basis;

    double m_fov;
};