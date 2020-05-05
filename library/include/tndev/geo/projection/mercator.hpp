#pragma once

#include <tndev/geo/latlng.hpp>
#include <tndev/geo/point.hpp>
#include <tndev/geo/tile.hpp>

#include <cmath>

namespace tndev::geo::projection {
struct mercator {
    mercator() = default;

    mercator(unsigned int tileX,
             unsigned int tileY,
             unsigned int level,
             unsigned int tileSize)
        : m_tile(tileX, tileY, level), m_tileSize(tileSize) {}

    mercator(const tile<mercator>& tile, unsigned int tileSize)
        : m_tile(tile), m_tileSize(tileSize) {}

    static auto to_relative(const latlng_rad& ll) -> point_value {
        auto res = point_value{};

        double latitude = degree(ll.lat()).count();
        double longitude = degree(ll.lng()).count();
        latitude = std::clamp(latitude, -85.05112878, 85.05112878);
        longitude = std::clamp(longitude, -180., 180.);

        double x = (longitude + 180.) / 360.;
        double sinLatitude =
            std::sin(latitude * kPI / 180.); // TODO use rad convert to RAD
        double y = 0.5 - std::log((1. + sinLatitude) / (1. - sinLatitude)) /
                             (4. * kPI);

        /*const auto mapSize = static_cast<double>(DstSize) *
                             static_cast<double>(std::pow(2, DstLevel));*/

        res.x = x;
        res.y = y;
        return res;
    }

    static auto to_latlng(const point_value& p) -> latlng_rad {
        auto res = tndev::geo::latlng_rad{};

        auto normalizedX = std::clamp(p.x, 0., 1.) - 0.5;
        auto normalizedY = 0.5 - std::clamp(p.y, 0., 1.);

        res.lat(degree(
            90. - 360. * std::atan(std::exp(-normalizedY * 2. * kPI)) / kPI));
        res.lng(degree(360. * normalizedX));

        return res;
    }

    auto projected(const point_value& relative) const -> point_value {
        auto projected = point_value{};

        const auto mapSize = static_cast<double>(m_tileSize) *
                             static_cast<double>(std::pow(2, m_tile.level()));

        projected.x = static_cast<double>(
                          std::clamp(relative.x * mapSize, 0., mapSize - 1.)) -
                      static_cast<double>(m_tile.x()) * m_tileSize;
        projected.y = static_cast<double>(
                          std::clamp(relative.y * mapSize, 0., mapSize - 1.)) -
                      static_cast<double>(m_tile.y()) * m_tileSize;

        return projected;
    }

    auto relative(const point_value& projected) const -> point_value {
        auto relative = point_value{};

        const auto mapSize = static_cast<double>(m_tileSize) *
                             static_cast<double>(std::pow(2, m_tile.level()));

        relative.x =
            (projected.x + static_cast<double>(m_tile.x()) * m_tileSize) /
            mapSize;
        relative.y =
            (projected.y + static_cast<double>(m_tile.y()) * m_tileSize) /
            mapSize;

        return relative;
    }

  private:
    // defines the offset and the scaling of the projection
    tile<mercator> m_tile;
    unsigned int m_tileSize = 256;
};
} // namespace tndev::geo::projection