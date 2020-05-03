#pragma once
#include <tndev/geo/extent.hpp>
#include <tndev/geo/latlng.hpp>

namespace tndev::geo {

struct latlng_elevation_trait;

template <angle_unit T>
struct latlng_elevation : public latlng<T> {
    using trait = latlng_elevation_trait;
    using value_type = double;
    using type = latlng_elevation;
    using angle_t = angle<T>;

    constexpr latlng_elevation() = default;
    constexpr latlng_elevation(const latlng_elevation& p) = default;
    ~latlng_elevation() noexcept = default;

    constexpr latlng_elevation(double lat_, double lng_)
        : latlng<T>(lat_, lng_) {}
    constexpr latlng_elevation(const angle_t& lat_, const angle_t& lng_)
        : latlng<T>(lat_, lng_) {}

    constexpr latlng_elevation(double lat_,
                               double lng_,
                               const meters& elevation)
        : latlng<T>(lat_, lng_), m_elevation(elevation) {}

    constexpr latlng_elevation(const angle_t& lat_,
                               const angle_t& lng_,
                               const meters& elevation)
        : latlng<T>(lat_, lng_), m_elevation(elevation) {}

    template <angle_unit S>
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr latlng_elevation(const latlng<S>& p) : latlng<T>(p) {}

    template <angle_unit S>
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr latlng_elevation(const latlng<S>& p, const meters& elevation)
        : latlng<T>(p), m_elevation(elevation) {}

    constexpr latlng_elevation(latlng_elevation&& p) noexcept = default;

    meters elevation() const { return m_elevation; }

  private:
    meters m_elevation = meters(0.);
};

using latlng_elevation_deg = latlng_elevation<angle_unit::kDeg>;
using latlng_elevation_rad = latlng_elevation<angle_unit::kRad>;

} // namespace tndev::geo