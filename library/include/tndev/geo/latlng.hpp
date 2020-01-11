#pragma once

#include <tndev/geo/angle.hpp>

#include <cmath>
#include <utility>

namespace tndev::geo {

template <angle_unit T>
struct latlng {
    using value_type = double;
    using type = latlng;
    using angle_t = angle<T>;

    constexpr latlng() = default;
    constexpr latlng(const latlng& p) = default;
    ~latlng() noexcept = default;

    constexpr latlng(double lat_, double lng_) : m_lat(lat_), m_lng(lng_) {}

    template <angle_unit S>
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr latlng(const latlng<S>& p) : m_lat(p.lat()), m_lng(p.lng()) {}

    constexpr latlng(latlng&& p) noexcept = default;

    constexpr auto lat() -> angle_t& { return m_lat; }
    constexpr auto lng() -> angle_t& { return m_lng; }

    constexpr auto lat() const -> angle_t& { return m_lat; }
    constexpr auto lng() const -> angle_t& { return m_lng; }

    constexpr auto operator=(const latlng& p) -> latlng& = default;
    constexpr auto operator=(latlng&& p) noexcept -> latlng& = default;

  private:
    angle_t m_lat = 0.;
    angle_t m_lng = 0.;
};

using latlng_deg = latlng<angle_unit::kDeg>;
using latlng_rad = latlng<angle_unit::kRad>;

template <typename T>
auto min(const T& a, const T& b) -> T {
    T res;

    res.lat = std::min(a.lat.count(), b.lat.count());
    res.lng = std::min(a.lng.count(), b.lng.count());

    return res;
}

template <typename T>
auto max(const T& a, const T& b) -> T {
    T res;

    res.lat = std::max(a.lat.count(), b.lat.count());
    res.lng = std::max(a.lng.count(), b.lng.count());

    return res;
}

} // namespace tndev::geo