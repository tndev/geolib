#include <catch2/catch.hpp>

#include <tndev/geo/latlng.distance.hpp>
#include <tndev/geo/latlng.hpp>
#include <tndev/geo/length.hpp>

TEST_CASE("calculate length deg", "[latlng.distance]") {
    using tndev::geo::distance;
    using tndev::geo::latlng_deg;
    using tndev::geo::latlng_rad;
    using tndev::geo::meters;

    auto llA = latlng_deg(46.363632, 8.536764);
    auto llB = latlng_deg(46.363632, 7.536764);

    auto distanceAB = meters(distance(llA, llB));

    REQUIRE(distanceAB.count() == Approx(76732.7810481685));
}

TEST_CASE("calculate length rad", "[latlng.distance]") {
    using tndev::geo::distance;
    using tndev::geo::latlng_deg;
    using tndev::geo::latlng_rad;
    using tndev::geo::meters;

    auto llA = latlng_deg(46.363632, 8.536764);
    auto llB = latlng_deg(46.363632, 7.536764);
    auto llARad = latlng_rad(llA);
    auto llBRad = latlng_rad(llB);

    auto distanceAB = meters(distance(llARad, llBRad));

    REQUIRE(distanceAB.count() == Approx(76732.7810481685));
}

TEST_CASE("calculate length deg 2", "[latlng.distance]") {
    using tndev::geo::distance;
    using tndev::geo::latlng_deg;
    using tndev::geo::latlng_rad;
    using tndev::geo::meters;

    auto llA = latlng_deg(47.691818, 9.187068);
    auto llB = latlng_deg(47.691402, 9.185451);
    auto llC = latlng_deg(47.691713, 9.186186);

    auto distanceAB = meters(distance(llA, llB, llC));

    REQUIRE(distanceAB.count() == Approx(12.6619829953));
}

TEST_CASE("calculate length deg 3", "[latlng.distance]") {
    using tndev::geo::distance;
    using tndev::geo::latlng_deg;
    using tndev::geo::latlng_rad;
    using tndev::geo::meters;

    auto llA = latlng_deg(47.691818, 9.187068);
    auto llB = latlng_deg(47.691402, 9.185451);
    auto llC = latlng_deg(47.691818, 9.187068);

    auto distanceAB = meters(distance(llA, llB, llC));

    REQUIRE(distanceAB.count() == Approx(0.));
}

TEST_CASE("calculate length deg 4", "[latlng.distance]") {
    using tndev::geo::distance;
    using tndev::geo::latlng_deg;
    using tndev::geo::latlng_rad;
    using tndev::geo::meters;

    auto llA = latlng_deg(47.691818, 9.187068);
    auto llB = latlng_deg(47.691402, 9.185451);
    auto llC = latlng_deg(47.692446, 9.189267);

    auto distanceAB = meters(distance(llA, llB, llC));
    auto distanceAC = meters(distance(llA, llC));

    REQUIRE(distanceAB.count() == distanceAC.count());
}

TEST_CASE("calculate length deg 5", "[latlng.distance]") {
    using tndev::geo::distance;
    using tndev::geo::latlng_deg;
    using tndev::geo::latlng_rad;
    using tndev::geo::meters;

    auto llA = latlng_deg(47.691818, 9.187068);
    auto llB = latlng_deg(47.691402, 9.185451);
    auto llC = latlng_deg(47.691120, 9.182780);

    auto distanceAB = meters(distance(llA, llB, llC));
    auto distanceAC = meters(distance(llB, llC));

    REQUIRE(distanceAB.count() == distanceAC.count());
}