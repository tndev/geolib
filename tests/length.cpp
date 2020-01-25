#include <catch2/catch.hpp>

#include <tndev/geo/latlng.hpp>
#include <tndev/geo/length.hpp>

TEST_CASE("calculate length deg", "[vector]") {
    using tndev::geo::distance;
    using tndev::geo::latlng_deg;
    using tndev::geo::latlng_rad;
    using tndev::geo::meters;

    auto llA = latlng_deg(46.363632, 8.536764);
    auto llB = latlng_deg(46.363632, 7.536764);

    auto distanceAB = length_cast<meters>(distance(llA, llB));

    REQUIRE(distanceAB.count() == Approx(76732.7810481685));
}

TEST_CASE("calculate length rad", "[vector]") {
    using tndev::geo::distance;
    using tndev::geo::latlng_deg;
    using tndev::geo::latlng_rad;
    using tndev::geo::meters;

    auto llA = latlng_deg(46.363632, 8.536764);
    auto llB = latlng_deg(46.363632, 7.536764);
    auto llARad = latlng_rad(llA);
    auto llBRad = latlng_rad(llB);

    auto distanceAB = length_cast<meters>(distance(llARad, llBRad));

    REQUIRE(distanceAB.count() == Approx(76732.7810481685));
}