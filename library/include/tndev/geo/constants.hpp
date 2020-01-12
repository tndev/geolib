#pragma once

namespace tndev::geo {

constexpr inline double kMinLatitude = -85.05112878;
constexpr inline double kMaxLatitude = 85.05112878;
constexpr inline double kHalfCircleDegree = 180.;
constexpr inline double kFullCircleDegree = 360.;
constexpr inline double kQuaterCircleDegree = 90.;
constexpr inline double kMinLongitude = -kHalfCircleDegree;
constexpr inline double kMaxLongitude = kHalfCircleDegree;

constexpr inline double kPI =
    3.1415926535897932384626433832795028841971693993751058209749445923078164062;

constexpr inline double kPI2 = kPI * 2.;

} // namespace tndev::geo