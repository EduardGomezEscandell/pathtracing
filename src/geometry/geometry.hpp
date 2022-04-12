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

    virtual std::optional<Hit> intersect(const Ray& ray) const = 0;

    virtual std::unique_ptr<Geometry> clone() const = 0;
protected:

private:
};