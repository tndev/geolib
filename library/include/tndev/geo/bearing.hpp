#pragma once

#include <tndev/geo/angle.hpp>
#include <tndev/geo/latlng.hpp>

#include <algorithm>
#include <cmath>
#include <tuple>

namespace tndev::geo {

template <angle_unit T>
struct bearing_trait;

template <>
struct bearing_trait<angle_unit::kDeg> {
    static constexpr const double kMaxAngle = 360.;
    static constexpr const double kHalfAngle = kMaxAngle / 2.;
};

template <>
struct bearing_trait<angle_unit::kRad> {
    static constexpr const double kMaxAngle = kPI * 2.;
    static constexpr const double kHalfAngle = kMaxAngle / 2.;
};

template <angle_unit Ta>
[[nodiscard]] constexpr auto normalize_bearing(const angle<Ta>& inputAngle) {
    auto maxAngle = bearing_trait<Ta>::kMaxAngle;

    auto result = inputAngle;
    if (result.count() < 0 || result.count() > maxAngle) {
        result = angle<Ta>(std::fmod(
            (std::fmod(result.count(), maxAngle) + maxAngle), maxAngle));
    }

    return result;
}

template <angle_unit R, angle_unit Ta, angle_unit Tb>
[[nodiscard]] constexpr auto calculate_bearing(const latlng<Ta>& from,
                                               const latlng<Tb>& to)
    -> angle<R> {
    auto fromRad = latlng_rad(from);
    auto toRad = latlng_rad(to);
    auto diffLng = toRad.lng() - fromRad.lng();

    auto y = std::sin(diffLng.count()) * std::cos(toRad.lat().count());
    auto x = std::cos(fromRad.lat().count()) * std::sin(toRad.lat().count()) -
             std::sin(fromRad.lat().count()) * std::cos(toRad.lat().count()) *
                 std::cos(diffLng.count());

    auto bearing = radian(std::atan2(y, x));

    return normalize_bearing(bearing);
}

template <angle_unit T>
struct bearing {
    using value_t = angle<T>;

    constexpr bearing() = default;

    template <angle_unit Ta, angle_unit Tb>
    constexpr bearing(const latlng<Ta>& from, const latlng<Tb>& to)
        : value(calculate_bearing<T>(from, to)) {}

    constexpr auto compass() const -> value_t { return value; }

    constexpr auto relative() const -> value_t {
        auto res = value;
        if (value.count() > bearing_trait<T>::kHalfAngle) {
            res = value_t(value.count() - bearing_trait<T>::kMaxAngle);
        }
        return res;
    }

    constexpr auto relative_abs() const -> value_t {
        auto res = value;
        if (value.count() > bearing_trait<T>::kHalfAngle) {
            res =
                value_t(std::abs(value.count() - bearing_trait<T>::kMaxAngle));
        }
        return res;
    }

  private:
    value_t value;
};

template <angle_unit T, angle_unit S>
auto smallest_angle_between_bearings(const bearing<S>& a, const bearing<T>& b) {
    auto minAngle = angle<T>{};
    auto maxAngle = angle<T>{};

    std::tie(minAngle, maxAngle) = std::minmax(a.compass(), b.compass());

    angle<T> res = maxAngle - minAngle;

    if (res.count() > bearing_trait<T>::kHalfAngle) {
        res = minAngle + (angle<T>(bearing_trait<T>::kMaxAngle) - maxAngle);
    }

    return res;
}

using bearing_deg = bearing<angle_unit::kDeg>;
using bearing_rad = bearing<angle_unit::kRad>;

} // namespace tndev::geo