#pragma once

#include <tndev/geo/constants.hpp>

#include <cmath>
#include <ratio>

// https://stackoverflow.com/questions/20231258/minimum-distance-between-a-point-and-a-line-in-latitude-longitude
// https://codereview.stackexchange.com/questions/157975/converting-between-miles-meters-inches-yards-and-feet/157988
// https://planetcalc.com/713/

namespace tndev::geo {

template <class Rep = double, class Period = std::ratio<1>>
struct length;

template <class Rep1, class Period1, class Rep2, class Period2>
constexpr auto length_cast_int(const length<Rep2, Period2>& in) -> Rep2;

template <class Rep, class Period>
struct length {
    using value_type = Rep;

    constexpr length() = default;
    constexpr explicit length(Rep val) : value(val) {}
    constexpr length(const length&) = default;
    constexpr length(length&&) noexcept = default;
    ~length() = default;

    template <class Rep2, class Period2>
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr length(const length<Rep2, Period2>& val)
        : value(length_cast_int<Rep, Period>(val)) {}

    constexpr auto operator=(const length& rhs) -> length& = default;
    constexpr auto operator=(length&& rhs) noexcept -> length& = default;

    [[nodiscard]] constexpr auto count() const -> Rep { return value; }

    [[nodiscard]] constexpr auto operator+() const -> length { return *this; }

    [[nodiscard]] constexpr auto operator-() const -> length {
        return length(-value);
    }

    constexpr auto operator+=(const length& len) -> length& {
        value += len.count();
        return *this;
    }

    constexpr auto operator-=(const length& len) -> length& {
        value -= len.count();
        return *this;
    }

    constexpr auto operator*=(const value_type& __rhs) -> length& {
        value *= __rhs;
        return *this;
    }

    constexpr auto operator/=(const value_type& __rhs) -> length& {
        value /= __rhs;
        return *this;
    }

  private:
    Rep value = 0;
};

using kilometers = length<double, std::kilo>;
using meters = length<double, std::ratio<1>>;
using centimeters = length<double, std::centi>;
using feet = length<double, std::ratio<3048, 10000>>;

template <class ToLength, class Rep, class Period>
constexpr auto length_cast(const length<Rep, Period>& d) -> ToLength {
    return ToLength(d);
}

template <class Rep1, class Period1, class Rep2, class Period2>
constexpr auto length_cast_int(const length<Rep2, Period2>& in) -> Rep2 {

    auto relTo =
        static_cast<Rep1>(Period1::num) / static_cast<Rep1>(Period1::den);
    auto relFrom =
        static_cast<Rep2>(Period2::num) / static_cast<Rep2>(Period2::den);
    return in.count() * relFrom / relTo;
}

template <class Rep1, typename Rep2, typename Period1, typename Period2>
[[nodiscard]] constexpr auto operator+(const length<Rep1, Period1>& lhs,
                                       const length<Rep2, Period2>& rhs)
    -> length<Rep1, Period1> {
    using return_t = length<Rep1, Period1>;
    return return_t(return_t(lhs).count() + return_t(rhs).count());
}

template <class Rep1, typename Rep2, typename Period1, typename Period2>
[[nodiscard]] constexpr auto operator-(const length<Rep1, Period1>& lhs,
                                       const length<Rep2, Period2>& rhs)
    -> length<Rep1, Period1> {
    using return_t = length<Rep1, Period1>;
    return return_t(return_t(lhs).count() - return_t(rhs).count());
}

template <class Rep1, typename Rep2, typename Period>
constexpr auto operator*(const length<Rep1, Period>& pt, const Rep2& val)
    -> length<Rep1, Period> {
    return length<Rep1, Period>{pt.count() * val};
}

template <class Rep1, typename Rep2, typename Period>
constexpr auto operator*(const Rep2& val, const length<Rep1, Period>& pt)
    -> length<Rep1, Period> {
    return length<Rep1, Period>{val * pt.count()};
}

template <class Rep1, typename Rep2, typename Period>
constexpr auto operator/(const length<Rep1, Period>& pt, const Rep2& val)
    -> length<Rep1, Period> {
    return length<Rep1, Period>{pt.count() / val};
}

template <class Rep1, typename Rep2, typename Period1, typename Period2>
[[nodiscard]] constexpr auto operator==(const length<Rep1, Period1>& lhs,
                                        const length<Rep2, Period2>& rhs)
    -> bool {
    return lhs.count() == length<Rep1, Period1>(rhs).count();
}

template <class Rep1, typename Rep2, typename Period1, typename Period2>
[[nodiscard]] constexpr auto operator!=(const length<Rep1, Period1>& lhs,
                                        const length<Rep2, Period2>& rhs)
    -> bool {
    return !(lhs == rhs);
}

template <class Rep1, typename Rep2, typename Period1, typename Period2>
[[nodiscard]] constexpr auto operator<(const length<Rep1, Period1>& lhs,
                                       const length<Rep2, Period2>& rhs)
    -> bool {
    return lhs.count() < length<Rep1, Period1>(rhs).count();
}

template <class Rep1, typename Rep2, typename Period1, typename Period2>
[[nodiscard]] constexpr auto operator>(const length<Rep1, Period1>& lhs,
                                       const length<Rep2, Period2>& rhs)
    -> bool {
    return rhs < lhs;
}

template <class Rep1, typename Rep2, typename Period1, typename Period2>
[[nodiscard]] constexpr auto operator<=(const length<Rep1, Period1>& lhs,
                                        const length<Rep2, Period2>& rhs)
    -> bool {
    return !(rhs < lhs);
}

template <class Rep1, typename Rep2, typename Period1, typename Period2>
[[nodiscard]] constexpr auto operator>=(const length<Rep1, Period1>& lhs,
                                        const length<Rep2, Period2>& rhs)
    -> bool {
    return !(rhs > lhs);
}

} // namespace tndev::geo

namespace tndev::geo_literals {

inline auto operator"" _m(long double val) -> geo::meters {
    return geo::meters(static_cast<double>(val));
}

inline auto operator"" _cm(long double val) -> geo::centimeters {
    return geo::centimeters(static_cast<double>(val));
}

inline auto operator"" _km(long double val) -> geo::kilometers {
    return geo::kilometers(static_cast<double>(val));
}

inline auto operator"" _ft(long double val) -> geo::feet {
    return geo::feet(static_cast<double>(val));
}

} // namespace tndev::geo_literals