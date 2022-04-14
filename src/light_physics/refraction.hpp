#pragma once

// STD includes
#include <numbers>

// External library includes
#include <Eigen/Dense>

// Project includes
#include "geometry/hit.hpp"
#include "rendering/light_ray.hpp"
#include "quadrature.hpp"

/** Using this paper to convert from square to circle GAuss quadratures:
 *
 * Shivaram, Kengeri. (2013). Gauss Legendre quadrature over a unit circle.
 * International Journal of Engineering and Technical Research. 
 * https://www.ijert.org/research/gauss-legendre-quadrature-over-a-unit-circle-IJERTV2IS90441.pdf.
 * Accessed 2022-14-04.
 */
template<Collocation TQuadrature>
class Refraction
{
public:
    Refraction() = default;

    auto generate_rays(Hit const& hit)
    {
        constexpr auto& collocation = get_collocation<TQuardrature>();
        std::array<LightRay, collocation.size()> rays;

        Eigen::Vector3d local_direction;

        auto i_ray = rays.begin();
        auto i_datum = collocation.begin();

        for(std::size_t i=0; i < collocation.size(); ++i)
        {
            // Converting from square to circle
            constexpr double radius = 0.5*(i_datum->xi + 1);
            constexpr double angle = 0.25*(i_datum->eta + 1)*std::numbers::pi;
            const double xi = radius * std::cos(angle);
            const double eta = radius * std::sin(angle);

            // Converting from circle to hemisphere
            const double phi = 0.4999*(xi + 1)*std::numbers::pi; // 0.499 to avoid covering the full hemisphere
            const double psi = 0.4999*(xi + 1)*std::numbers::pi; // 0.499 to avoid covering the full hemisphere

            const double u = std::cos(phi)*cos(psi);
            const double v = std::cos(phi)*sin(psi);
            const double w = std::sqrt(1 - u*u - v*v)

            local_direction = Eigen::Vector3d {u, v, w};

            i_ray->direction = m_local_basis * local_direction;

            ++i_ray;
            ++i_datum;
        }

        return rays;
    }

    Color integrate_color(std::array<LightRay, get_collocation_size<TQuardrature>()> const& rays)
    {
        double acc_red   = 0;
        double acc_green = 0;
        double acc_blue  = 0;
        double acc_alpha = 0;

        constexpr auto& collocation = get_collocation<TQuardrature>();

        auto i_ray = rays.cbegin();
        auto i_datum = collocation.cbegin();

        for(std::size_t i=0; i < collocation.size(); ++i)
        {
            const double weight = i_datum->weight * (i_datum->xi + 1) * std::numbers::pi / 16.0;

            acc_red    +=weight * i_ray->color.r;
            acc_green  +=weight * i_ray->color.g;
            acc_blue   +=weight * i_ray->color.b;
            acc_alpha  +=weight * i_ray->color.a;

            ++i_datum;
            ++i_ray;
        }

        const auto red   = static_cast<Color::channel>(acc_red);
        const auto green = static_cast<Color::channel>(acc_green);
        const auto blue  = static_cast<Color::channel>(acc_blue);
        const auto alpha = static_cast<Color::channel>(acc_alpha);

        return {red, green, blue, alpha};
    }
};