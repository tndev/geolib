#include <catch2/catch.hpp>

#include <tndev/geo/latlng.hpp>
#include <tndev/geo/point.hpp>
#include <tndev/geo/projection/mercator.hpp>
#include <tndev/geo/quadkey.hpp>
#include <tndev/geo/tile.hpp>

TEST_CASE("projectioning back and forth 1", "[projection]") {
    using tndev::geo::latlng_deg;
    using tndev::geo::point;
    using tndev::geo::projection::mercator;

    auto ll = latlng_deg(46.363632, 8.536764);

    auto p1 = point<mercator>(ll);
    auto m = mercator();
    auto p2 = point<mercator>(p1.projected(m), m);

    REQUIRE(p1.x() == Approx(p2.x()));
    REQUIRE(p1.y() == Approx(p2.y()));
}

TEST_CASE("projectioning back and forth 2", "[projection]") {
    using tndev::geo::latlng_deg;
    using tndev::geo::point;
    using tndev::geo::projection::mercator;

    auto ll = latlng_deg(46.363632, 8.536764);

    auto p1 = point<mercator>(ll);
    auto m = mercator(1, 2, 5, 256);
    auto p2 = point<mercator>(p1.projected(m), m);

    REQUIRE(p1.x() == Approx(p2.x()));
    REQUIRE(p1.y() == Approx(p2.y()));
}

TEST_CASE("projectioning back and forth 3", "[projection]") {
    using tndev::geo::latlng_deg;
    using tndev::geo::point;
    using tndev::geo::projection::mercator;

    auto ll = latlng_deg(46.363632, 8.536764);

    auto p1 = point<mercator>(ll);
    auto m = mercator(5, 2, 5, 512);
    auto p2 = point<mercator>(p1.projected(m), m);

    REQUIRE(p1.x() == Approx(p2.x()));
    REQUIRE(p1.y() == Approx(p2.y()));
}

TEST_CASE("quadkey", "[projection]") {
    using tndev::geo::quadkey_to_tile;
    using tndev::geo::tile;
    using tndev::geo::tile_to_quadkey;
    using tndev::geo::projection::mercator;

    auto tileOrg = tile<mercator>(1, 1, 2);
    auto quadkey = tile_to_quadkey(tileOrg);

    REQUIRE(quadkey == "03");

    auto tile2 = quadkey_to_tile<mercator>(quadkey);

    REQUIRE(tileOrg.x() == Approx(tile2.x()));
    REQUIRE(tileOrg.y() == Approx(tile2.y()));
    REQUIRE(tileOrg.level() == Approx(tile2.level()));
}