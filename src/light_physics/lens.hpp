#pragma once

// STD includes
#include <array>

// External library includes
#include <Eigen/Dense>

// Project includes
#include "rendering/light_ray.hpp"
#include "quadrature.hpp"

template<Collocation TQuadrature>
class Lens
{
public:
    Lens(Eigen::Matrix3d const& local_basis,
         std::size_t width,
         std::size_t height,
         const double fov
    ) : m_local_basis(local_basis),
        m_du{1.0 / (0.5 * width)},
        m_dv{- 1.0 / (0.5 * height)}
    {
        const double aspect_ratio = height / static_cast<double>(width);
        m_hfov = fov * 0.5;
        m_vfov = m_hfov * aspect_ratio;
    }

    auto generate_rays(
        const std::size_t row,
        const std::size_t col)
    {
        constexpr auto& collocation = get_collocation<C>();
        std::array<LightRay, collocation.size()> rays;

        const double origin_u = -1.0 + (col+0.5)*m_du ;
        const double origin_v =  1.0 + (row+0.5)*m_dv;

        Eigen::Vector3d local_direction;

        auto i_ray = rays.begin();
        auto i_datum = collocation.begin();

        for(std::size_t i=0; i < collocation.size(); ++i)
        {
            const double u = origin_u + 0.5 * m_du * i_datum->xi;
            const double v = origin_v + 0.5 * m_dv * i_datum->eta;

            local_direction = {
                std::tan(m_hfov * u),
                std::tan(m_vfov * v),
                1
            };
            local_direction.normalize();
            i_ray->direction = m_local_basis * local_direction;

            ++i_ray;
            ++i_datum;
        }

        return rays;
    }

    Color integrate_color(std::array<LightRay, get_collocation_size<C>()> const& rays)
    {
        double acc_red   = 0;
        double acc_green = 0;
        double acc_blue  = 0;
        double acc_alpha = 0;

        constexpr auto& collocation = get_collocation<C>();

        auto i_ray = rays.cbegin();
        auto i_datum = collocation.cbegin();

        for(std::size_t i=0; i < collocation.size(); ++i)
        {
            acc_red    += i_datum->weight * i_ray->color.r;
            acc_green  += i_datum->weight * i_ray->color.g;
            acc_blue   += i_datum->weight * i_ray->color.b;
            acc_alpha  += i_datum->weight * i_ray->color.a;

            ++i_datum;
            ++i_ray;
        }

        const auto red   = static_cast<Color::channel>(acc_red);
        const auto green = static_cast<Color::channel>(acc_green);
        const auto blue  = static_cast<Color::channel>(acc_blue);
        const auto alpha = static_cast<Color::channel>(acc_alpha);

        return {red, green, blue, alpha};
    }

private:
    Eigen::Matrix3d const& m_local_basis;
    double m_du;
    double m_dv;
    double m_hfov;
    double m_vfov;
};