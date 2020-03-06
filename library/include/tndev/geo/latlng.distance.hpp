#pragma once

#include <tndev/geo/bearing.hpp>
#include <tndev/geo/latlng.hpp>
#include <tndev/geo/length.hpp>

namespace tndev::geo {

// haversine
template <class Rep = double,
          class Period = std::ratio<1>,
          angle_unit T,
          angle_unit S>
[[nodiscard]] auto distance(const latlng<T>& p1, const latlng<S>& p2)
    -> length<Rep, Period> {
    // https://www.movable-type.co.uk/scripts/latlong.html
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

template <class Rep = double,
          class Period = std::ratio<1>,
          angle_unit S,
          angle_unit E,
          angle_unit P>
auto distance(const latlng<S>& start,
              const latlng<P>& end,
              const latlng<E>& point) -> length<Rep, Period> {
    // https://stackoverflow.com/questions/20231258/minimum-distance-between-a-point-and-a-line-in-latitude-longitude
    // https://www.movable-type.co.uk/scripts/latlong.html
    using tndev::geo::length_cast;
    using tndev::geo_literals::operator""_deg;

    auto bearingStartPoint = bearing_rad(start, point);
    auto bearingStartEnd = bearing_rad(start, end);

    auto distanceStartPoint = kilometers(distance(start, point));

    auto angleA = smallest_angle_between_bearings(bearing_deg(start, point),
                                                  bearing_deg(start, end));
    auto angleB = smallest_angle_between_bearings(bearing_deg(end, point),
                                                  bearing_deg(end, start));

    auto result = length<Rep, Period>(0.);

    if (angleA > 90._deg) {
        result = distance(start, point);
    } else if (angleB > 90._deg) {
        result = distance(end, point);
    } else {
        auto tmpDistance =
            std::asin(std::sin(distanceStartPoint.count() / kEarthMeanRadius) *
                      std::sin(bearingStartPoint.relative().count() -
                               bearingStartEnd.relative().count())) *
            kEarthMeanRadius;
        result = kilometers(tmpDistance);
    }

    return result;
}

} // namespace tndev::geo