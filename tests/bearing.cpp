
#include <catch2/catch.hpp>

#include "tndev/geo/angle.hpp"
#include <tndev/geo/bearing.hpp>
#include <tndev/geo/constants.hpp>

TEST_CASE("normalize bearing deg", "[bearing]") {
    using tndev::geo::degree;
    using tndev::geo::normalize_bearing;

    auto normalizedA = normalize_bearing(degree(365.));
    auto normalizedB = normalize_bearing(degree(-5.));

    REQUIRE(normalizedA.count() == Approx(5.));
    REQUIRE(normalizedB.count() == Approx(355.));
}

TEST_CASE("normalize bearing rad", "[bearing]") {
    using tndev::geo::kPI2;
    using tndev::geo::normalize_bearing;
    using tndev::geo::radian;

    auto normalizedA = normalize_bearing(radian(kPI2 + 0.1));
    auto normalizedB = normalize_bearing(radian(-0.1));

    REQUIRE(normalizedA.count() == Approx(0.1));
    REQUIRE(normalizedB.count() == Approx(kPI2 - 0.1));
}

TEST_CASE("calculate bearing deg", "[bearing]") {
    using tndev::geo::angle_unit;
    using tndev::geo::calculate_bearing;
    using tndev::geo::latlng_deg;

    auto center = latlng_deg(47.691626, 9.186317);
    auto north = latlng_deg(47.692030, 9.186282);

    auto bearingCenterNorth =
        calculate_bearing<angle_unit::kDeg>(center, north);
    auto bearingNorthCenter =
        calculate_bearing<angle_unit::kDeg>(north, center);
    REQUIRE(bearingCenterNorth.count() == Approx(356.6626076389));
    REQUIRE(bearingNorthCenter.count() == Approx(176.6625817551));
}

TEST_CASE("compass bearing", "[bearing]") {
    using tndev::geo::bearing_deg;
    using tndev::geo::latlng_deg;

    auto center = latlng_deg(47.691626, 9.186317);
    auto north = latlng_deg(47.692030, 9.186282);

    auto centerNorth = bearing_deg(center, north);
    auto northCenter = bearing_deg(north, center);

    REQUIRE(centerNorth.compass().count() == Approx(356.6626076389));
    REQUIRE(northCenter.compass().count() == Approx(176.6625817551));
}

TEST_CASE("relative bearing", "[bearing]") {
    using tndev::geo::bearing_deg;
    using tndev::geo::latlng_deg;

    auto center = latlng_deg(47.691626, 9.186317);
    auto north = latlng_deg(47.692030, 9.186282);

    auto centerNorth = bearing_deg(center, north);
    auto northCenter = bearing_deg(north, center);

    REQUIRE(centerNorth.relative().count() == Approx(-3.3373923611));
    REQUIRE(northCenter.relative().count() == Approx(176.6625817551));
}

TEST_CASE("relative absolute bearing", "[bearing]") {
    using tndev::geo::bearing_deg;
    using tndev::geo::latlng_deg;

    auto center = latlng_deg(47.691626, 9.186317);
    auto north = latlng_deg(47.692030, 9.186282);
    // auto south = latlng_deg(47.691145, 9.186357);
    // auto east = latlng_deg(47.691640, 9.186845);
    // auto west = latlng_deg(47.691593, 9.185574);

    auto centerNorth = bearing_deg(center, north);
    auto northCenter = bearing_deg(north, center);

    REQUIRE(centerNorth.relative_abs().count() == Approx(3.3373923611));
    REQUIRE(northCenter.relative_abs().count() == Approx(176.6625817551));
}