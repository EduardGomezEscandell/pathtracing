#pragma once

// STD includes
#include <numeric>
#include <array>

// External library includes
#include <Eigen/Dense>

// Project includes
#include "image/image.hpp"
#include "rendering/light_ray.hpp"


enum class Collocation {
    CENTER,
    LOBATTO,
    GAUSS_4,
    GAUSS_9,
};


template<std::size_t NumPoints>
struct Quadrature {

    struct QuadraturePoint
    {
        double weight;
        double xi;
        double eta;
    };

    std::array<QuadraturePoint, NumPoints> data;
    static constexpr auto size() noexcept {return NumPoints; }

    constexpr auto cbegin() const noexcept { return data.cbegin(); }
    constexpr auto cend() const noexcept { return data.cend(); }
    
    constexpr auto begin() const noexcept { return cbegin(); }
    constexpr auto end() const noexcept { return cend(); }

private:
    constexpr void validate()
    {
        constexpr double sum_weights = std::accumulate(data.begin(), data.end(), 0.0, [](double acc, const QuadraturePoint& p) { return acc + p.weight; } );
        static_assert(std::abs(sum_weights - 1.0) < 1e-8, "Quadrature weights must sum to 1");
    }
};

namespace Quadratures {

static constexpr Quadrature<4> center {
    QuadraturePoint{1.0, 0.0, 0.0}
};

static constexpr Quadrature<4> lobatto {
    QuadraturePoint{0.25, -1.0, -1.0},
    QuadraturePoint{0.25,  1.0, -1.0},
    QuadraturePoint{0.25, -1.0,  1.0},
    QuadraturePoint{0.25,  1.0,  1.0}
};

static constexpr Quadrature<4> gauss_4 {
    QuadraturePoint{0.25, -0.57735026919, -0.57735026919},
    QuadraturePoint{0.25,  0.57735026919, -0.57735026919},
    QuadraturePoint{0.25, -0.57735026919,  0.57735026919},
    QuadraturePoint{0.25,  0.57735026919,  0.57735026919}
};

static constexpr Quadrature<9> gauss_9 {
    QuadraturePoint{25/324.0, -0.77459666924, -0.77459666924},
    QuadraturePoint{25/324.0,  0.77459666924, -0.77459666924},
    QuadraturePoint{25/324.0, -0.77459666924,  0.77459666924},
    QuadraturePoint{25/324.0,  0.77459666924,  0.77459666924},
    QuadraturePoint{40/324.0,  0.0          , -0.77459666924},
    QuadraturePoint{40/324.0,  0.0,            0.77459666924},
    QuadraturePoint{40/324.0, -0.77459666924,  0.0          },
    QuadraturePoint{40/324.0,  0.77459666924,  0.0          },
    QuadraturePoint{64/324.0,  0.0,            0.0          },
};

template<Collocation C>
constexpr auto& get_collocation()
{
    if constexpr(C == Collocation::CENTER) return center;
    if constexpr(C == Collocation::LOBATTO) return lobatto;
    if constexpr(C == Collocation::GAUSS_4) return gauss_4;
    if constexpr(C == Collocation::GAUSS_9) return gauss_9;
}

template<Collocation C>
constexpr std::size_t get_collocation_size()
{
    return get_collocation<C>().size();
}

}