#include <catch2/catch.hpp>

#include <tndev/geo/length.hpp>

TEST_CASE("convert meters to kilometers", "[length]") {
    using tndev::geo::kilometers;
    using tndev::geo::meters;
    REQUIRE(kilometers(meters(1500.)).count() == Approx(1.5));
}

TEST_CASE("convert kilometers to meters", "[length]") {
    using tndev::geo::kilometers;
    using tndev::geo::meters;
    REQUIRE(meters(kilometers(1.5)).count() == Approx(1500.));
}

TEST_CASE("multiply by scalar 1", "[length]") {
    using tndev::geo::kilometers;
    using tndev::geo::meters;
    REQUIRE((meters(1500.) * 2.).count() == Approx(3000.));
}

TEST_CASE("multiply by scalar 2", "[length]") {
    using tndev::geo::kilometers;
    using tndev::geo::meters;
    REQUIRE((2. * meters(1500.)).count() == Approx(3000.));
}

TEST_CASE("divide by scalar", "[length]") {
    using tndev::geo::kilometers;
    using tndev::geo::meters;
    REQUIRE((meters(1500.) / 2.).count() == Approx(750.));
}

TEST_CASE("default constructor", "[length]") {
    using tndev::geo::kilometers;

    kilometers len;

    REQUIRE(len.count() == Approx(0.));
}

TEST_CASE("default copy constructor", "[length]") {
    using tndev::geo::kilometers;

    auto len = kilometers(kilometers(1.5));

    REQUIRE(len.count() == Approx(1.5));
}

TEST_CASE("assign meters to kilometers", "[length]") {
    using tndev::geo::kilometers;
    using tndev::geo::meters;

    kilometers len;
    len = meters(1500.);

    REQUIRE(len.count() == Approx(1.5));
}

TEST_CASE("negate length", "[length]") {
    using tndev::geo::kilometers;
    using tndev::geo::meters;

    kilometers len = -kilometers(1.5);

    REQUIRE(len.count() == Approx(-1.5));
}

TEST_CASE("unary plus", "[length]") {
    using tndev::geo::kilometers;
    using tndev::geo::meters;

    kilometers len = +kilometers(1.5);

    REQUIRE(len.count() == Approx(1.5));
}