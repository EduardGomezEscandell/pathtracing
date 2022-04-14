#pragma once

// STD includes
#include <numbers>

// External library includes
#include <Eigen/Dense>

// Project includes
#include "geometry/hit.hpp"
#include "rendering/light_ray.hpp"
#include "quadrature.hpp"

template<Collocation TQuadrature>
class Refraction
{
public:
    Refraction() = default;

    auto generate_rays(Hit const& hit)
    {
        constexpr auto& collocation = get_hemisphere_collocation<TQuadrature>();
        static_assert(collocation.size() > 0); // Forcing compiler into compile-time creation of collocation

        std::array<LightRay, collocation.size()> rays;

        const auto basis = ComputeLocalBasis(hit.normal);

        auto i_ray = rays.begin();
        auto i_datum = collocation.begin();

        for(std::size_t i=0; i < collocation.size(); ++i)
        {
            Eigen::Vector3d local_direction {
                i_datum->xi,
                i_datum->eta,
                i_datum->nu
            };

            i_ray->direction = basis * local_direction;

            ++i_ray;
            ++i_datum;
        }

        return rays;
    }

    Color integrate_color(std::array<LightRay, get_collocation_size<TQuadrature>()> const& rays)
    {
        double acc_red   = 0;
        double acc_green = 0;
        double acc_blue  = 0;
        double acc_alpha = 0;

        constexpr auto& collocation = get_hemisphere_collocation<TQuadrature>();
        static_assert(collocation.size() > 0); // Forcing compiler into compile-time creation of collocation

        auto i_ray = rays.cbegin();
        auto i_datum = collocation.cbegin();

        for(std::size_t i=0; i < collocation.size(); ++i)
        {
            const double weight = i_datum->weight * (i_datum->xi + 1) * std::numbers::pi / 16.0;

            acc_red   += weight * i_ray->color.r;
            acc_green += weight * i_ray->color.g;
            acc_blue  += weight * i_ray->color.b;
            acc_alpha += weight * i_ray->color.a;

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

    Eigen::Matrix3d ComputeLocalBasis(Eigen::Vector2d const& normal)
    {
        static constexpr double epsilon = 1e-8;
        assert(std::abs(normal.norm() - 1.0) < epsilon); // normal should be normalized

        Eigen::Matrix3d basis = Eigen::Matrix3d::Identity();

        auto u = basis.col(0);
        auto v = basis.col(1);
        auto w = basis.col(2);

        w = normal;

        if(std::abs(w[0] - 1.0) > epsilon) // normal is not along X
        {
            v = w.cross(u);
        }
        else // normal is along X
        {
            u = v.cross(w);
        }

        // Gramm-Schmidt orthonormalization
        u = u - w.dot(u)*w;
        u.normalize();

        v = w - u.dot(v)*u - w.dot(v)*w;
        v.normalize();

        return basis;
    }

};