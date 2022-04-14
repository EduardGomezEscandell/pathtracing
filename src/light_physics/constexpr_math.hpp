#pragma once

// STD includes
#include <numbers>
#include <cmath>

// External library includes

// Project includes


namespace constexpr_math {

// These functions are hidden to avoid pollution the namespace.
// Only intended to be used within this file.
namespace
{
    static constexpr double PI = std::numbers::pi;

    constexpr long long int fact(const unsigned int x)
    {
        if(x <= 1) return x;
        return x*fact(x-1); // tail recursion
    }

    constexpr double pow(const double x, const std::size_t n)
    {
        if(n == 0) return 1;
        return x*pow(x, n-1); // tail recursion
    }

    constexpr double mod(const double x, const double base)
    {
        return x - base*static_cast<long long int>(x / base);
    }
}

constexpr double sin(const double x);

constexpr double cos(const double x)
{
    if(!std::is_constant_evaluated()) {
        return std::cos(x);
    }

    const double y = mod(x, 2*PI);

    if(x < 0.0)  return constexpr_math::cos(-x);
    if(y > PI)   return -constexpr_math::cos(y - PI);
    if(y > PI/2) return -constexpr_math::sin(y - PI/2);
    if(y > PI/4) return  constexpr_math::sin(PI/2 - y);

    // Taylor series
    return 1 - pow(y,2)/fact(2)
             + pow(y,4)/fact(4)
             - pow(y,6)/fact(6)
             + pow(y,8)/fact(8)
             - pow(y,10)/fact(10)
             + pow(y,12)/fact(12);
}

constexpr double sin(const double x)
{
    if(!std::is_constant_evaluated()) {
        return std::sin(x);
    }

    const double y = mod(x, 2*PI);

    if(x < 0.0)  return -constexpr_math::sin(-x);
    if(y > PI)   return -constexpr_math::sin(y - PI);
    if(y > PI/2) return  constexpr_math::sin(PI - y);
    if(y > PI/4) return  constexpr_math::cos(PI/2 - y);

    // Taylor series
    return + pow(y,1)/fact(1)
           - pow(y,3)/fact(3)
           + pow(y,5)/fact(5)
           - pow(y,7)/fact(7)
           + pow(y,9)/fact(9)
           - pow(y,11)/fact(11);
}


/** Compile-time tests!
 * Namespace created to avoid polluting constexpr_math namespace.
 */
namespace constexpr_unit_testing
{
    static constexpr double epsilon = 1e-10;

    constexpr bool almost_equal(const double x, const double y)
    {
        return std::abs(x - y) < epsilon;
    }

    static_assert(almost_equal(sin(-80), 0.993888653923));
    static_assert(almost_equal(cos(-80), -0.110387243839));

    static_assert(almost_equal(sin(1000), 0.826879540532));
    static_assert(almost_equal(cos(1000), 0.562379076291));

    static_assert(almost_equal(sin(3.5), -0.35078322769));
    static_assert(almost_equal(cos(3.5), -0.936456687291));

    static_assert(almost_equal(sin(2.7), 0.427379880234));
    static_assert(almost_equal(cos(2.7), -0.904072142017));

    static_assert(almost_equal(sin(0.4), 0.389418342309));
    static_assert(almost_equal(cos(0.4), 0.921060994003));
}

}