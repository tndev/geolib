#pragma once

#include <tndev/geo/constants.hpp>

#include <cmath>
#include <ratio>

// https://stackoverflow.com/questions/20231258/minimum-distance-between-a-point-and-a-line-in-latitude-longitude
// https://codereview.stackexchange.com/questions/157975/converting-between-miles-meters-inches-yards-and-feet/157988
// https://planetcalc.com/713/

namespace tndev::geo {

template <class Rep = double, class Period = std::ratio<1>>
struct extent;

template <class Rep1, class Period1, class Rep2, class Period2>
constexpr auto extent_cast_int(const extent<Rep2, Period2>& in) -> Rep2;

template <class Rep, class Period>
struct extent {
    using value_type = Rep;

    constexpr extent() = default;
    constexpr explicit extent(Rep val) : value(val) {}
    constexpr extent(const extent&) = default;
    constexpr extent(extent&&) noexcept = default;
    ~extent() = default;

    template <class Rep2, class Period2>
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr extent(const extent<Rep2, Period2>& val)
        : value(extent_cast_int<Rep, Period>(val)) {}

    constexpr auto operator=(const extent& rhs) -> extent& = default;
    constexpr auto operator=(extent&& rhs) noexcept -> extent& = default;

    [[nodiscard]] constexpr auto count() const -> Rep { return value; }

    [[nodiscard]] constexpr auto operator+() const -> extent { return *this; }

    [[nodiscard]] constexpr auto operator-() const -> extent {
        return extent(-value);
    }

    constexpr auto operator+=(const extent& len) -> extent& {
        value += len.count();
        return *this;
    }

    constexpr auto operator-=(const extent& len) -> extent& {
        value -= len.count();
        return *this;
    }

    constexpr auto operator*=(const value_type& __rhs) -> extent& {
        value *= __rhs;
        return *this;
    }

    constexpr auto operator/=(const value_type& __rhs) -> extent& {
        value /= __rhs;
        return *this;
    }

  private:
    Rep value = 0;
};

using kilometers = extent<double, std::kilo>;
using meters = extent<double, std::ratio<1>>;
using centimeters = extent<double, std::centi>;
using feet = extent<double, std::ratio<3048, 10000>>;

template <class ToExtent, class Rep, class Period>
constexpr auto extent_cast(const extent<Rep, Period>& d) -> ToExtent {
    return ToExtent(d);
}

template <class Rep1, class Period1, class Rep2, class Period2>
constexpr auto extent_cast_int(const extent<Rep2, Period2>& in) -> Rep2 {

    auto relTo =
        static_cast<Rep1>(Period1::num) / static_cast<Rep1>(Period1::den);
    auto relFrom =
        static_cast<Rep2>(Period2::num) / static_cast<Rep2>(Period2::den);
    return in.count() * relFrom / relTo;
}

template <class Rep1, typename Rep2, typename Period1, typename Period2>
[[nodiscard]] constexpr auto operator+(const extent<Rep1, Period1>& lhs,
                                       const extent<Rep2, Period2>& rhs)
    -> extent<Rep1, Period1> {
    using return_t = extent<Rep1, Period1>;
    return return_t(return_t(lhs).count() + return_t(rhs).count());
}

template <class Rep1, typename Rep2, typename Period1, typename Period2>
[[nodiscard]] constexpr auto operator-(const extent<Rep1, Period1>& lhs,
                                       const extent<Rep2, Period2>& rhs)
    -> extent<Rep1, Period1> {
    using return_t = extent<Rep1, Period1>;
    return return_t(return_t(lhs).count() - return_t(rhs).count());
}

template <class Rep1, typename Rep2, typename Period>
constexpr auto operator*(const extent<Rep1, Period>& pt, const Rep2& val)
    -> extent<Rep1, Period> {
    return extent<Rep1, Period>{pt.count() * val};
}

template <class Rep1, typename Rep2, typename Period>
constexpr auto operator*(const Rep2& val, const extent<Rep1, Period>& pt)
    -> extent<Rep1, Period> {
    return extent<Rep1, Period>{val * pt.count()};
}

template <class Rep1, typename Rep2, typename Period>
constexpr auto operator/(const extent<Rep1, Period>& pt, const Rep2& val)
    -> extent<Rep1, Period> {
    return extent<Rep1, Period>{pt.count() / val};
}

template <class Rep1, typename Rep2, typename Period1, typename Period2>
[[nodiscard]] constexpr auto operator==(const extent<Rep1, Period1>& lhs,
                                        const extent<Rep2, Period2>& rhs)
    -> bool {
    return lhs.count() == extent<Rep1, Period1>(rhs).count();
}

template <class Rep1, typename Rep2, typename Period1, typename Period2>
[[nodiscard]] constexpr auto operator!=(const extent<Rep1, Period1>& lhs,
                                        const extent<Rep2, Period2>& rhs)
    -> bool {
    return !(lhs == rhs);
}

template <class Rep1, typename Rep2, typename Period1, typename Period2>
[[nodiscard]] constexpr auto operator<(const extent<Rep1, Period1>& lhs,
                                       const extent<Rep2, Period2>& rhs)
    -> bool {
    return lhs.count() < extent<Rep1, Period1>(rhs).count();
}

template <class Rep1, typename Rep2, typename Period1, typename Period2>
[[nodiscard]] constexpr auto operator>(const extent<Rep1, Period1>& lhs,
                                       const extent<Rep2, Period2>& rhs)
    -> bool {
    return rhs < lhs;
}

template <class Rep1, typename Rep2, typename Period1, typename Period2>
[[nodiscard]] constexpr auto operator<=(const extent<Rep1, Period1>& lhs,
                                        const extent<Rep2, Period2>& rhs)
    -> bool {
    return !(rhs < lhs);
}

template <class Rep1, typename Rep2, typename Period1, typename Period2>
[[nodiscard]] constexpr auto operator>=(const extent<Rep1, Period1>& lhs,
                                        const extent<Rep2, Period2>& rhs)
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