#pragma once

#include <tndev/geo/latlng.hpp>
#include <tndev/geo/length.hpp>

#include <ratio>

namespace tndev::geo {

template <class Rep = double,
          class Period = std::ratio<1>,
          angle_unit T,
          angle_unit S>
[[nodiscard]] constexpr auto distance(const latlng<T>& p1, const latlng<S>& p2)
    -> length<Rep, Period> {

    auto lat1 = radian(p1.lat()).count();
    auto lat2 = radian(p2.lat()).count();
    auto lng1 = radian(p1.lng()).count();
    auto lng2 = radian(p2.lng()).count();

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