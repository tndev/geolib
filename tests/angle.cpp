#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

// #include <tndev/geo/angle.hpp>

//

TEST_CASE("deg to rad", "[single-file]") {
    using tndev::geo::angle_cast;
    using tndev::geo::degree;
    using tndev::geo::radian;

    auto angRad0Deg = angle_cast<radian>(degree(0.));
    auto angRad45Deg = angle_cast<radian>(degree(45.));
    auto angRad90Deg = angle_cast<radian>(degree(90.));
    auto angRad180Deg = angle_cast<radian>(degree(180.));
    auto angRad360Deg = angle_cast<radian>(degree(360.));

    REQUIRE(angRad0Deg.count() == Approx(0));
    REQUIRE(angRad45Deg.count() == Approx(0.785398));
    REQUIRE(angRad90Deg.count() == Approx(1.5708));
    REQUIRE(angRad180Deg.count() == Approx(3.14159));
    REQUIRE(angRad360Deg.count() == Approx(6.28318));
}

TEST_CASE("deg literal", "[single-file]") {
    using namespace tndev::geo_literals;

    REQUIRE((45._deg).count() == Approx(45));
    REQUIRE((90._deg).count() == Approx(90));
    REQUIRE((180._deg).count() == Approx(180));
}

TEST_CASE("rad literal", "[single-file]") {
    using namespace tndev::geo_literals;
    using tndev::geo::angle_cast;
    using tndev::geo::degree;
    using tndev::geo::radian;

    REQUIRE((0.785398_rad).count() == Approx(0.785398));
    REQUIRE((6.28318_rad).count() == Approx(6.28318));

    REQUIRE(angle_cast<degree>(0.785398_rad).count() == Approx(45));
    REQUIRE(angle_cast<degree>(6.28318_rad).count() == Approx(360));
}
