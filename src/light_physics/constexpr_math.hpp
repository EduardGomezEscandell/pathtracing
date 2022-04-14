#pragma once

// STD includes
#include <numbers>
#include <cmath>

// External library includes

// Project includes


namespace constexpr_math {

// These functions are hidden to avoid polluting the namespace.
// Only intended to be used within this file.
namespace
{
    static constexpr double PI = std::numbers::pi;

    constexpr long long int factorial(const unsigned int x)
    {
        if(x <= 1) return x;
        return x*factorial(x-1); // tail recursion
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
    return 1 - pow(y,2)/factorial(2)
             + pow(y,4)/factorial(4)
             - pow(y,6)/factorial(6)
             + pow(y,8)/factorial(8)
             - pow(y,10)/factorial(10)
             + pow(y,12)/factorial(12);
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
    return + pow(y,1)/factorial(1)
           - pow(y,3)/factorial(3)
           + pow(y,5)/factorial(5)
           - pow(y,7)/factorial(7)
           + pow(y,9)/factorial(9)
           - pow(y,11)/factorial(11)
           + pow(y,13)/factorial(13);
}

} // namespace constexpr_math
