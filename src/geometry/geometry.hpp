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

    virtual ~Geometry() = default;

    virtual std::optional<Hit> intersect(const Ray& ray) = 0;
protected:

private:
};