#pragma once

#include <tndev/geo/bounding_box.hpp>
#include <tndev/geo/latlng.hpp>
#include <tndev/geo/point.hpp>

#include <cmath>

namespace tndev::geo {
template <typename Projection>
struct tile {
    tile() = default;
    tile(const tile&) = default;
    tile(tile&&) noexcept = default;
    ~tile() = default;

    tile(unsigned int x, unsigned int y, unsigned int level)
        : m_x(x), m_y(y), m_level(level) {}

    constexpr auto operator=(const tile& p) -> tile& = default;
    constexpr auto operator=(tile&& p) noexcept -> tile& = default;

    auto x() const { return m_x; }

    auto y() const { return m_y; }

    auto level() const { return m_level; }

  private:
    unsigned int m_x = 0;
    unsigned int m_y = 0;
    unsigned int m_level = 0;
};

template <typename Projection>
auto get_enclosing_tile(const point<Projection>& p, unsigned int level) {

    auto numOfTiles = std::pow(2, level);

    auto tileX = std::floor(numOfTiles * p.x());
    auto tileY = std::floor(numOfTiles * p.y());

    return tile<Projection>(static_cast<unsigned int>(tileX),
                            static_cast<unsigned int>(tileY), level);
}

template <typename Projection, angle_unit T>
auto get_enclosing_tile(const latlng<T>& ll, unsigned int level) {
    return get_enclosing_tile(point<Projection>(ll), level);
}

template <typename Projection>
auto get_bounding_box_point(const tile<Projection>& tile) {
    using point_t = point<Projection>;
    auto tiles = static_cast<double>(std::pow(2, tile.level()));

    auto x1 = tile.x() / tiles;
    auto y1 = tile.y() / tiles;
    auto x2 = (tile.x() + 1.) / tiles;
    auto y2 = (tile.y() + 1.) / tiles;

    return bounding_box<point_t>(point_t({x1, y1}), point_t({x2, y2}));
}

template <typename Projection>
auto get_bounding_box_latlng(const tile<Projection>& tile) {
    using latlng_t = latlng_rad;

    auto bboxPoint = get_bounding_box_point(tile);

    return bounding_box<latlng_t>(bboxPoint.topleft().latlng(),
                                  bboxPoint.bottomright().latlng());
}

} // namespace tndev::geo