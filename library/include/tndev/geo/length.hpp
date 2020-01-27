#pragma once

#include <tndev/geo/constants.hpp>
#include <tndev/geo/latlng.hpp>

#include <cmath>
#include <iostream>
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
    template <class Rep2, class Period2>
    constexpr explicit length(const length<Rep2, Period2>& val)
        : value(length_cast_int<Rep, Period>(val)) {}

    constexpr explicit length(Rep val) : value(val) {}

    [[nodiscard]] constexpr auto count() const -> Rep { return value; }

  private:
    Rep value;
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

template <class Rep = double,
          class Period = std::ratio<1>,
          angle_unit T,
          angle_unit S>
auto distance(const latlng<T>& p1, const latlng<S>& p2) -> length<Rep, Period> {

    auto lat1 = angle<angle_unit::kRad>(p1.lat()).count();
    auto lat2 = angle<angle_unit::kRad>(p2.lat()).count();
    auto lng1 = angle<angle_unit::kRad>(p1.lng()).count();
    auto lng2 = angle<angle_unit::kRad>(p2.lng()).count();

    auto u = std::sin((lat2 - lat1) / 2.0);
    auto v = std::sin((lng2 - lng1) / 2.0);

    auto earthRadius = kilometers(kEarthMeanRadius);

    // std::cout << earthRadius.count() << std::endl;

    auto result =
        earthRadius * 2.0 *
        std::asin(std::sqrt(u * u + std::cos(lat1) * std::cos(lat2) * v * v));

    return length<Rep, Period>(result);
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