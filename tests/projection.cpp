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

TEST_CASE("back and forth projection", "[projection]") {
    using tndev::geo::degree;
    using tndev::geo::get_enclosing_tile;
    using tndev::geo::latlng_deg;
    using tndev::geo::point;
    using tndev::geo::projection::mercator;

    auto ll = latlng_deg(47.691603, 9.186170);
    auto llTile = get_enclosing_tile<mercator>(ll, 18);

    auto p1 = point<mercator>(ll);
    auto m = mercator(llTile, 256);
    auto projected = p1.projected(m);
    auto p2 = point<mercator>(projected, m);
    auto ll2 = p2.latlng();

    REQUIRE(degree(ll.lat()).count() == Approx(degree(ll2.lat()).count()));
    REQUIRE(degree(ll.lng()).count() == Approx(degree(ll2.lng()).count()));
}

TEST_CASE("get projected point", "[projection]") {

    using tndev::geo::degree;
    using tndev::geo::get_enclosing_tile;
    using tndev::geo::latlng_deg;
    using tndev::geo::point;
    using tndev::geo::projection::mercator;

    auto ll = latlng_deg(47.691603, 9.186170);
    auto llTile = get_enclosing_tile<mercator>(ll, 18);

    auto p1 = point<mercator>(ll);
    auto m = mercator(llTile, 256);
    auto projected = p1.projected(m);

    REQUIRE(projected.x == Approx(42.2034));
    REQUIRE(projected.y == Approx(165.687));
}

TEST_CASE("verify bbox projected", "[projection]") {
    using tndev::geo::degree;
    using tndev::geo::get_enclosing_tile;
    using tndev::geo::latlng_deg;
    using tndev::geo::point;
    using tndev::geo::projection::mercator;

    auto ll = latlng_deg(47.691603, 9.186170);
    auto llTile = get_enclosing_tile<mercator>(ll, 18);

    auto bbox = get_bounding_box_point(llTile);
    auto m = mercator(bbox, 256);
    auto tl = bbox.topleft();
    auto br = bbox.bottomright();

    auto tlProjected = tl.projected(m);
    auto brProjected = br.projected(m);

    REQUIRE(tlProjected.x == Approx(0.0));
    REQUIRE(tlProjected.y == Approx(0.0));
    REQUIRE(brProjected.x == Approx(256.0));
    REQUIRE(brProjected.y == Approx(256.0));
}