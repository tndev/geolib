#include <catch2/catch.hpp>

#include <tndev/geo/latlng.hpp>
#include <tndev/geo/length.hpp>

TEST_CASE("calculate lngth", "[vector]") {
    using tndev::geo::distance;
    using tndev::geo::kilometers;
    using tndev::geo::latlng_deg;

    auto llA = latlng_deg(46.363632, 8.536764);
    auto llB = latlng_deg(46.363632, 7.536764);

    auto distanceAB = length_cast<kilometers>(distance(llA, llB));

    REQUIRE(distanceAB.count() == Approx(76732.7810481685));
}