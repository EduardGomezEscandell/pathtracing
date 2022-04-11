#pragma once

// STD includes
#include <optional>

// External library includes
#include <Eigen/Dense>

// Project includes
#include "ray.hpp"
#include "hit.hpp"


class Geometry
{
public:
    Geometry() = default;
    virtual std::optional<Hit> Intersect(const Ray& ray) = 0;
protected:

private:
};