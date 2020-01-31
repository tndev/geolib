#pragma once

#include <tndev/geo/angle.hpp>
#include <tndev/geo/latlng.hpp>

#include <cmath>

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
inline constexpr auto normalize_bearing(const angle<Ta>& inputAngle) {
    auto maxAngle = bearing_trait<Ta>::kMaxAngle;

    auto result = inputAngle;
    if (result.count() < 0 || result.count() > maxAngle) {
        result = angle<Ta>(std::fmod(
            (std::fmod(result.count(), maxAngle) + maxAngle), maxAngle));
    }

    return result;
}

template <angle_unit R, angle_unit Ta, angle_unit Tb>
inline constexpr auto calculate_bearing(const latlng<Ta>& from,
                                        const latlng<Tb>& to) -> angle<R> {
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
        : angle(calculate_bearing<T>(from, to)) {}

    constexpr auto compass() const -> value_t { return angle; }

    constexpr auto relative() const -> value_t {
        auto res = angle;
        if (angle.count() > bearing_trait<T>::kHalfAngle) {
            res = value_t(angle.count() - bearing_trait<T>::kMaxAngle);
        }
        return res;
    }

    constexpr auto relative_abs() const -> value_t {
        auto res = angle;
        if (angle.count() > bearing_trait<T>::kHalfAngle) {
            res =
                value_t(std::abs(angle.count() - bearing_trait<T>::kMaxAngle));
        }
        return res;
    }

  private:
    value_t angle;
};

using bearing_deg = bearing<angle_unit::kDeg>;
using bearing_rad = bearing<angle_unit::kRad>;

} // namespace tndev::geo