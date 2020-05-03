
#include <catch2/catch.hpp>

#include <tndev/geo/latlng_elevation.hpp>

TEST_CASE("default elevation", "[latlng_elevation]") {
    using tndev::geo::latlng_elevation_deg;

    auto llA = latlng_elevation_deg(46.363632, 8.536764);

    REQUIRE(llA.elevation().count() == Approx(0.));
}

TEST_CASE("defined elevation", "[latlng_elevation]") {
    using tndev::geo::latlng_elevation_deg;
    using tndev::geo::meters;

    auto llA = latlng_elevation_deg(46.363632, 8.536764, meters(10.));

    REQUIRE(llA.elevation().count() == Approx(10.));
}