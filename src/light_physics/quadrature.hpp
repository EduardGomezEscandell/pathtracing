#pragma once

// STD includes
#include <numeric>
#include <array>

// External library includes
#include <Eigen/Dense>

// Project includes
#include "constexpr_math.hpp"
#include "image/image.hpp"
#include "rendering/light_ray.hpp"


enum class Collocation {
    CENTER,
    LOBATTO,
    GAUSS_2,
    GAUSS_3,
    GAUSS_4,
    GAUSS_5,
};

struct QuadraturePoint
{
    double weight = 0;
    double xi = 0;
    double eta = 0;
    double nu = 0;
};

template<std::size_t NumPoints>
struct Quadrature
{
    static_assert(NumPoints > 0, "Number of points must be greater than 0");

    constexpr Quadrature() = default;

    template<typename ... Args>
    constexpr Quadrature(Args ... args)
        : data{args...}
    {
        static_assert(sizeof...(args) == NumPoints, "Number of points must match the number of arguments");
        validate();
    }

    static constexpr auto size() noexcept {return NumPoints; }

    constexpr auto cbegin() const noexcept { return data.cbegin(); }
    constexpr auto cend() const noexcept { return data.cend(); }

    constexpr auto begin() const noexcept { return cbegin(); }
    constexpr auto end() const noexcept { return cend(); }

    constexpr auto begin() noexcept { return data.begin(); }
    constexpr auto end() noexcept { return data.end(); }

private:
    std::array<QuadraturePoint, NumPoints> data;

    constexpr void validate() const
    {
        [[maybe_unused]] const double sum_weights =
            std::accumulate(data.begin(), data.end(), 0.0, [](double acc, const QuadraturePoint& p) { return acc + p.weight; } );

        assert(constexpr_math::constexpr_unit_testing::almost_equal(sum_weights, 1.0)); // If this fails during compilation, the sum of the weights is not one.
    }
};

namespace Quadratures {

static constexpr Quadrature<1> center {
    QuadraturePoint{1.0, 0.0, 0.0}
};

static constexpr Quadrature<2> lobatto {
    QuadraturePoint{0.5, -1.0},
    QuadraturePoint{0.5,  1.0}
};

static constexpr Quadrature<2> gauss_2 {
    QuadraturePoint{0.5, -0.57735026919},
    QuadraturePoint{0.5,  0.57735026919}
};

static constexpr Quadrature<3> gauss_3 {
    QuadraturePoint{5.0/18.0, -0.77459666924},
    QuadraturePoint{5.0/18.0,  0.77459666924},
    QuadraturePoint{8.0/18.0,  0.0}
};

static constexpr Quadrature<4> gauss_4 {
    QuadraturePoint{0.1739274225687269, -0.8611363115940526},
    QuadraturePoint{0.3260725774312731, -0.3399810435848563},
    QuadraturePoint{0.3260725774312731, 0.3399810435848563},
    QuadraturePoint{0.1739274225687269, 0.8611363115940526}
};

static constexpr Quadrature<5> gauss_5 {
    QuadraturePoint{0.2844444444444444, 0.0000000000000000},
    QuadraturePoint{0.2393143352496833, -0.5384693101056831},
    QuadraturePoint{0.2393143352496833, 0.5384693101056831},
    QuadraturePoint{0.1184634425280945, -0.9061798459386640},
    QuadraturePoint{0.1184634425280945, 0.9061798459386640}
};

template<Collocation C>
constexpr auto& get_collocation()
{
    if constexpr(C == Collocation::CENTER) return center;
    if constexpr(C == Collocation::LOBATTO) return lobatto;
    if constexpr(C == Collocation::GAUSS_2) return gauss_2;
    if constexpr(C == Collocation::GAUSS_3) return gauss_3;
    if constexpr(C == Collocation::GAUSS_4) return gauss_4;
    if constexpr(C == Collocation::GAUSS_5) return gauss_5;
}

template <Collocation C>
constexpr auto get_square_collocation()
{
    constexpr auto line_collocation = get_collocation<C>();
    constexpr auto n = line_collocation.size();

    Quadrature<n*n> square_collocation;
    auto it_quadrature_point = square_collocation.begin();

    for(auto const& point_i: line_collocation)
    {
        for(auto const& point_j: line_collocation)
        {
            it_quadrature_point->xi  = point_i.xi;
            it_quadrature_point->eta = point_j.xi;
            it_quadrature_point->weight = point_i.weight * point_j.weight;
            ++it_quadrature_point;
        }
    }

    return square_collocation;
}

/** Using this paper to convert
 *   - from [-1,-1] x [-1, 1] square Gauss quadratures
 *   - to unit circle quadratures
 *
 * Shivaram, Kengeri. (2013). Gauss Legendre quadrature over a unit circle.
 * International Journal of Engineering and Technical Research.
 * https://www.ijert.org/research/gauss-legendre-quadrature-over-a-unit-circle-IJERTV2IS90441.pdf.
 * Accessed 2022-14-04.
 */
template <Collocation C>
constexpr auto get_circle_collocation()
{
    using constexpr_math::cos;
    using constexpr_math::sin;

    constexpr auto n = get_collocation<C>().size();

    constexpr auto square_collocation = get_square_collocation<C>();
    constexpr auto circle_collocation = Quadrature< 4 * square_collocation.size() >{};

    for(std::size_t j=0; j<4*n*n; ++j)
    {
        constexpr auto i = j % square_collocation.size();
        constexpr double angle_offset = 0.5*std::numbers::pi * j/square_collocation.size();

        constexpr double radius = 0.5*(square_collocation[i].xi + 1);
        constexpr double angle = 0.25*(square_collocation[i].eta + 1)*std::numbers::pi + angle_offset;

        circle_collocation[i*n + j].xi  = radius * cos(angle);
        circle_collocation[i*n + j].eta = radius * sin(angle);
        circle_collocation[i*n + j].weight = square_collocation[i].weight * (square_collocation[i].xi + 1) * std::numbers::pi / 16.0;
    }

    return circle_collocation;
}

template <Collocation C>
constexpr auto get_hemisphere_collocation()
{
    using constexpr_math::cos;
    using constexpr_math::sin;

    constexpr auto collocation = get_circle_collocation<C>();

    for(auto& cp: collocation)
    {
        constexpr double phi = cp.xi;
        constexpr double psi = cp.eta;

        cp.xi  = sin(phi) * cos(psi);
        cp.eta = sin(phi) * sin(psi);
        cp.nu  = cos(phi);
    }

    return collocation;
}
}
