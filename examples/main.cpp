#include <iostream>
#include <tndev/geo/angle.hpp>

auto main() -> int {
    using namespace tndev::geo_literals;

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

    std::cout << rad.count() << std::endl;
    std::cout << (rad < deg40) << std::endl;
    std::cout << (deg40 < rad) << std::endl;

    return 0;
}