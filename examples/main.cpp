#include <tndev/geo/angle.hpp>
#include <tndev/geo/bearing.hpp>
#include <tndev/geo/latlng.distance.hpp>
#include <tndev/geo/latlng.hpp>
#include <tndev/geo/point.hpp>
#include <tndev/geo/projection/mercator.hpp>
#include <tndev/geo/quadkey.hpp>
#include <tndev/geo/tile.hpp>

#include <iostream>

auto main() -> int {
    using tndev::geo_literals::operator""_deg;
    using tndev::geo::degree;
    using tndev::geo::distance;
    using tndev::geo::extent_cast;
    using tndev::geo::latlng_deg;
    using tndev::geo::meters;
    using tndev::geo::point;
    using tndev::geo::radian;
    using tndev::geo::tile;
    using tndev::geo::projection::mercator;

    auto deg90 = tndev::geo::degree(90.);
    auto deg40 = tndev::geo::degree(40.);

    auto deg = tndev::geo::degree(90.);
    auto rad = tndev::geo::radian(45._deg);

    std::cout << deg.count() << std::endl;

    std::cout << rad.count() << std::endl;

    rad = rad / 2.;

    std::cout << (deg90 / 2.).count() << std::endl;

    std::cout << rad.count() << std::endl;

    rad = -rad;

    auto center = latlng_deg(47.691626, 9.186317);
    auto north = latlng_deg(47.692030, 9.186282);
    auto south = latlng_deg(47.691145, 9.186357);
    auto east = latlng_deg(47.691640, 9.186845);

    auto centerTile = get_enclosing_tile<mercator>(center, 18);
    std::cout << "qk: " << tile_to_quadkey(centerTile) << std::endl;

    auto p1 = point<mercator>(center);
    auto t = tile<mercator>();
    auto t1 = tile<mercator>(1, 1, 2);
    auto m = mercator(5, 5, 2, 512);
    std::cout << "qk: " << tile_to_quadkey(t1) << std::endl;
    auto t2 = tndev::geo::quadkey_to_tile<mercator>(tile_to_quadkey(t1));

    auto p2 = point<mercator>(p1.projected(m), m);

    std::cout << "rel   : " << p1.x() << " " << p1.y() << std::endl;
    std::cout << "rel2  : " << p2.x() << " " << p2.y() << std::endl;
    std::cout << "prj   : " << p1.projected(m).x << " " << p1.projected(m).y
              << std::endl;
    auto p1ll = p1.latlng();
    std::cout << "ll    : " << p1ll.lat().count() << " " << p1ll.lng().count()
              << std::endl;
    std::cout << "orgll : " << radian(center.lat()).count() << " "
              << radian(center.lng()).count() << std::endl;

    auto west = latlng_deg(47.691593, 9.185574);

    std::cout << "bearing center -> north  "
              << tndev::geo::bearing_deg(center, north).relative().count()
              << std::endl;
    std::cout << "bearing north -> center  "
              << tndev::geo::bearing_deg(north, center).relative().count()
              << std::endl;
    std::cout << "bearing center -> west  "
              << tndev::geo::bearing_deg(center, west).relative().count()
              << std::endl;
    std::cout << "bearing west -> center  "
              << tndev::geo::bearing_deg(west, center).relative().count()
              << std::endl;
    std::cout << "bearing center -> east  "
              << tndev::geo::bearing_deg(center, east).relative().count()
              << std::endl;
    std::cout << "bearing east -> center  "
              << tndev::geo::bearing_deg(east, center).relative().count()
              << std::endl;

    /*auto llA = latlng_deg(47.691818, 9.187068);
    auto llB = latlng_deg(47.691402, 9.185451);
    auto llC1 = latlng_deg(47.692035, 9.187787);
    auto llC2 = latlng_deg(47.691402, 9.185451);
    auto llC3 = latlng_deg(47.691645, 9.186220);
    auto llC4 = latlng_deg(47.694164, 9.194955);

    std::cout << "bearing A  --> B  " << degree(bearing(llA, llB)).count()
              << std::endl;
    std::cout << "bearing B  --> A  " << degree(bearing(llB, llA)).count()
              << std::endl;
    std::cout << "bearing A  --> C1 " << degree(bearing(llA, llC1)).count()
              << std::endl;
    std::cout << "bearing C1 --> A  " << degree(bearing(llC1, llA)).count()
              << std::endl;

    auto distanceAB1 = length_cast<meters>(distance(llA, llB, llC1));
    auto distanceAB2 = length_cast<meters>(distance(llA, llB, llC2));
    auto distanceAB3 = length_cast<meters>(distance(llA, llB, llC3));
    auto distanceAB4 = length_cast<meters>(distance(llA, llB, llC4));

    std::cout << "* " << distanceAB1.count() << std::endl;
    std::cout << "* " << distanceAB2.count() << std::endl;
    std::cout << "* " << distanceAB3.count() << std::endl;
    std::cout << "* " << distanceAB4.count() << std::endl;*/

    std::cout << rad.count() << std::endl;
    std::cout << (rad < deg40) << std::endl;
    std::cout << (deg40 < rad) << std::endl;

    return 0;
}