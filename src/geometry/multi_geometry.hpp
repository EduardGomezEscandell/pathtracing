#pragma once

// STD includes
#include <memory>

// External library includes

// Project includes
#include "geometry.hpp"


class MultiGeometry : public Geometry
{
public:
    MultiGeometry() : Geometry() { }

    MultiGeometry(MultiGeometry && other);

    MultiGeometry(MultiGeometry const& other);

    std::optional<Hit> intersect(const Ray& ray) const override;

    std::unique_ptr<Geometry> clone() const override;

    template<std::derived_from<Geometry> TGeometryType>
    Geometry& push(TGeometryType && geometry)
    {
        return emplace<TGeometryType>(geometry);
    }

    template<std::derived_from<Geometry> TGeometryType>
    Geometry& emplace(TGeometryType && geometry)
    {
        m_geometries.emplace_back(std::make_unique<TGeometryType>(geometry));
        return *m_geometries.back();
    }

    template<std::derived_from<Geometry> TGeometryType, typename ...Args>
    Geometry& emplace(Args const& ... args)
    {
        m_geometries.emplace_back(std::make_unique<TGeometryType>(args...));
        return *m_geometries.back();
    }

    std::unique_ptr<Geometry> pop();

    auto size() const noexcept { return m_geometries.size(); }

protected:
    std::vector<std::unique_ptr<Geometry>> m_geometries;
};