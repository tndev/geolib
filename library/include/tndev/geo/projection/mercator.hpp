#pragma once

#include <tndev/geo/bounding_box.hpp>
#include <tndev/geo/latlng.hpp>
#include <tndev/geo/point.hpp>
#include <tndev/geo/tile.hpp>

#include <cmath>
#include <algorithm>

namespace tndev::geo::projection {
struct mercator {
    using point_t = point<mercator>;
    mercator() : m_bbox(point_t({0., 0.}), point_t({1., 1.})) {}

    explicit mercator(const bounding_box<point_t>& bbox, unsigned int tileSize = 256.)
        : m_bbox(bbox), m_tileSize(tileSize) {}

    template <angle_unit T>
    explicit mercator(const bounding_box<latlng<T>>& bbox, unsigned int tileSize = 256.)
        : mercator(bounding_box<point_t>(point_t(bbox.topleft()),
                                         point_t(bbox.bottomright())),
                   tileSize) {}

    explicit mercator(const tile<mercator>& tile, unsigned int tileSize = 256.)
        : mercator(get_bounding_box_point(tile), tileSize) {}

    mercator(unsigned int tileX,
             unsigned int tileY,
             unsigned int level,
             unsigned int tileSize = 256.)
        : mercator(tile<mercator>(tileX, tileY, level), tileSize) {}

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

        auto relativeTileWitdh =
            m_bbox.bottomright().x() - m_bbox.topleft().x();
        auto relativeTileHeight =
            m_bbox.bottomright().y() - m_bbox.topleft().y();

        projected.x = (relative.x - m_bbox.topleft().x()) / relativeTileWitdh *
                      m_tileSize;
        projected.y = (relative.y - m_bbox.topleft().y()) / relativeTileHeight *
                      m_tileSize;

        return projected;
    }

    auto relative(const point_value& projected) const -> point_value {
        auto relative = point_value{};

        auto relativeTileWitdh =
            m_bbox.bottomright().x() - m_bbox.topleft().x();
        auto relativeTileHeight =
            m_bbox.bottomright().y() - m_bbox.topleft().y();

        relative.x = (projected.x / m_tileSize) * relativeTileWitdh +
                     m_bbox.topleft().x();
        relative.y = (projected.y / m_tileSize) * relativeTileHeight +
                     m_bbox.topleft().y();

        return relative;
    }

  private:
    // defines the offset and the scaling of the projection
    bounding_box<point_t> m_bbox;
    unsigned int m_tileSize = 256;
};
} // namespace tndev::geo::projection