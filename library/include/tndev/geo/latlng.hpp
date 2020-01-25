#pragma once

#include <tndev/geo/angle.hpp>

#include <cmath>
#include <utility>

// https://stackoverflow.com/questions/20231258/minimum-distance-between-a-point-and-a-line-in-latitude-longitude
namespace tndev::geo {

struct latlng_trait;

template <angle_unit T>
struct latlng {
    using trait = latlng_trait;
    using value_type = double;
    using type = latlng;
    using angle_t = angle<T>;

    constexpr latlng() = default;
    constexpr latlng(const latlng& p) = default;
    ~latlng() noexcept = default;

    constexpr latlng(double lat_, double lng_) : m_lat(lat_), m_lng(lng_) {}
    constexpr latlng(const angle_t& lat_, const angle_t& lng_)
        : m_lat(lat_), m_lng(lng_) {}

    template <angle_unit S>
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr latlng(const latlng<S>& p) : m_lat(p.lat()), m_lng(p.lng()) {}

    constexpr latlng(latlng&& p) noexcept = default;

    constexpr void lat(const angle_t& lat) { m_lat = lat; }
    constexpr void lng(const angle_t& lng) { m_lng = lng; }
    
    constexpr auto lat() const -> const angle_t& { return m_lat; }
    constexpr auto lng() const -> const angle_t& { return m_lng; }

    constexpr auto operator=(const latlng& p) -> latlng& = default;
    constexpr auto operator=(latlng&& p) noexcept -> latlng& = default;

  private:
    angle_t m_lat = angle_t{0.};
    angle_t m_lng = angle_t{0.};
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