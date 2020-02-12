#pragma once

#include <tndev/geo/constants.hpp>

namespace tndev::geo {

enum class angle_unit { kDeg, kRad };

template <angle_unit F, angle_unit T>
constexpr auto convert_angle(double in) {
    return in;
}

template <>
constexpr auto convert_angle<angle_unit::kDeg, angle_unit::kRad>(double in) {
    return in * kPI / kHalfCircleDegree;
}

template <>
constexpr auto convert_angle<angle_unit::kRad, angle_unit::kDeg>(double in) {
    return in * kHalfCircleDegree / kPI;
}

template <angle_unit T>
struct angle {
    using value_type = double;

    constexpr angle() = default;
    explicit constexpr angle(value_type val) : value(val) {}
    constexpr angle(const angle&) = default;
    constexpr angle(angle&&) noexcept = default;
    ~angle() = default;

    template <angle_unit S>
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr angle(const angle<S> ang)
        : value(convert_angle<S, T>(ang.count())) {}

    [[nodiscard]] constexpr auto count() const { return value; }

    constexpr auto operator=(const angle& rhs) -> angle& = default;
    constexpr auto operator=(angle&& rhs) noexcept -> angle& = default;

    [[nodiscard]] constexpr auto operator+() const -> angle { return *this; }

    [[nodiscard]] constexpr auto operator-() const -> angle {
        return angle(-value);
    }

    constexpr auto operator+=(const angle& ang) -> angle& {
        value += ang.count();
        return *this;
    }

    constexpr auto operator-=(const angle& ang) -> angle& {
        value -= ang.count();
        return *this;
    }

    constexpr auto operator*=(const value_type& __rhs) -> angle& {
        value *= __rhs;
        return *this;
    }

    constexpr auto operator/=(const value_type& __rhs) -> angle& {
        value /= __rhs;
        return *this;
    }

  private:
    value_type value = 0;
};

using degree = angle<angle_unit::kDeg>;
using radian = angle<angle_unit::kRad>;

template <angle_unit T1, angle_unit T2>
[[nodiscard]] constexpr auto operator+(const angle<T1>& lhs,
                                       const angle<T2>& rhs) -> angle<T1> {
    using return_t = angle<T1>;
    return return_t(return_t(lhs).count() + return_t(rhs).count());
}

template <angle_unit T1, angle_unit T2>
[[nodiscard]] constexpr auto operator-(const angle<T1>& lhs,
                                       const angle<T2>& rhs) -> angle<T1> {
    using return_t = angle<T1>;
    return return_t(return_t(lhs).count() - return_t(rhs).count());
}

template <angle_unit T1, typename Period>
[[nodiscard]] constexpr auto operator*(const angle<T1>& lhs, const Period& s)
    -> angle<T1> {
    using return_t = angle<T1>;
    return return_t(return_t(lhs).count() * s);
}

template <angle_unit T1, typename Period>
[[nodiscard]] constexpr auto operator/(const angle<T1>& lhs, const Period& s)
    -> angle<T1> {
    using return_t = angle<T1>;
    return return_t(return_t(lhs).count() / s);
}

template <angle_unit T1, angle_unit T2>
[[nodiscard]] constexpr auto operator==(const angle<T1>& lhs,
                                        const angle<T2>& rhs) -> bool {
    return lhs.count() == angle<T1>(rhs).count();
}

template <angle_unit T1, angle_unit T2>
[[nodiscard]] constexpr auto operator!=(const angle<T1>& lhs,
                                        const angle<T2>& rhs) -> bool {
    return !(lhs == rhs);
}

template <angle_unit T1, angle_unit T2>
[[nodiscard]] constexpr auto operator<(const angle<T1>& lhs,
                                       const angle<T2>& rhs) -> bool {
    return lhs.count() < angle<T1>(rhs).count();
}

template <angle_unit T1, angle_unit T2>
[[nodiscard]] constexpr auto operator>(const angle<T1>& lhs,
                                       const angle<T2>& rhs) -> bool {
    return rhs < lhs;
}

template <angle_unit T1, angle_unit T2>
[[nodiscard]] constexpr auto operator<=(const angle<T1>& lhs,
                                        const angle<T2>& rhs) -> bool {
    return !(rhs < lhs);
}

template <angle_unit T1, angle_unit T2>
[[nodiscard]] constexpr auto operator>=(const angle<T1>& lhs,
                                        const angle<T2>& rhs) -> bool {
    return !(rhs > lhs);
}

template <class ToAngle, angle_unit T>
[[nodiscard]] constexpr auto angle_cast(const angle<T>& in) -> ToAngle {
    return ToAngle(in);
}

} // namespace tndev::geo

namespace tndev::geo_literals {
inline auto operator"" _deg(long double val) {
    return geo::degree(static_cast<double>(val));
}

inline auto operator"" _rad(long double val) {
    return geo::radian(static_cast<double>(val));
}
} // namespace tndev::geo_literals