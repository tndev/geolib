#pragma once

#include <tndev/geo/latlng.hpp>

namespace tndev::geo {

struct point_value {
    double x = 0.;
    double y = 0.;
};

template <typename Projection>
struct point {
    using value_t = point_value;

    point() = default;
    ~point() = default;
    point(const point&) = default;
    point(point&&) noexcept = default;

    constexpr auto operator=(const point& p) -> point& = default;
    constexpr auto operator=(point&& p) noexcept -> point& = default;

    template <angle_unit T>
    explicit point(const latlng<T>& ll)
        : m_value(Projection::to_relative(ll)){};

    point(const point_value& projected, const Projection& projection)
        : m_value(projection.relative(projected)){};

    // relavtive coordinates in projection space
    [[nodiscard]] constexpr auto x() const { return m_value.x; }
    [[nodiscard]] constexpr auto y() const { return m_value.y; }

    [[nodiscard]] auto projected(const Projection& projection) const
        -> point_value {
        return projection.projected(m_value);
    }

    [[nodiscard]] constexpr auto latlng() const -> latlng_rad {
        // TODO convert relative cordiantes back to latlng
        return Projection::to_latlng(m_value);
    }

  private:
    point_value m_value;
};

} // namespace tndev::geo