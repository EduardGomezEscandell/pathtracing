#pragma once

// STD includes
#include <numeric>

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


namespace
{

struct QuadraturePoint {
    double weight;
    double xi;
    double eta;
};

template<std::size_t NumPoints>
struct Quadrature {
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

    template<Collocation C>
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

    template<Collocation C>
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