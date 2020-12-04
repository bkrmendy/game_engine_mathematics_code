#include <catch2/catch.hpp>

#include <array>
#include <rapidcheck.h>

#include "../src/Vector/Vector.h"
#include "../src/Utility/FloatingPointEquals.h"

using namespace GEM;

TEST_CASE("Vector operations", "[Vectors]")
{
    SECTION("Vector negation", "[Vector]")
    {
        rc::check("Vector negation", [](std::array<double, 3> elems) {
            Vector<3, double> vec{ elems };
            auto result = vec.negate();
            REQUIRE(Utility::equals(vec.at(0) + result.at(0), 0.0));
            REQUIRE(Utility::equals(vec.at(1) + result.at(1), 0.0));
            REQUIRE(Utility::equals(vec.at(2) + result.at(2), 0.0));
        });
    }

    SECTION("Vector-scalar addition", "[Vector]")
    {
        Vector<3, int> v1{ { 1, 2, 3 } };
        rc::check("Vector scalar addition", [&v1](const int scalar) {
            auto result = v1 + scalar;
            REQUIRE(result.at(0) == v1.at(0) + scalar);
            REQUIRE(result.at(1) == v1.at(1) + scalar);
            REQUIRE(result.at(2) == v1.at(2) + scalar);
        });
    }

    SECTION("Vector-scalar multiplication", "[Vector]")
    {
        Vector<3, int> v1{ { 1, 2, 3 } };
        rc::check("Vector-scalar multiplication", [&v1](const int scalar) {
            auto result = v1 * scalar;
            REQUIRE(result.at(0) == v1.at(0) * scalar);
            REQUIRE(result.at(1) == v1.at(1) * scalar);
            REQUIRE(result.at(2) == v1.at(2) * scalar);
        });
    }

    SECTION("Vector-scalar division", "[Vector]")
    {
        Vector<3, double> v1{ { 1, 2, 3 } };
        rc::check("Vector-scalar division", [&v1](const double scalar) {
            RC_PRE(!Utility::equals(scalar, 0.0));

            auto result = v1 / scalar;
            REQUIRE(Utility::equals(result.at(0), v1.at(0) / scalar));
            REQUIRE(Utility::equals(result.at(1), v1.at(1) / scalar));
            REQUIRE(Utility::equals(result.at(2), v1.at(2) / scalar));
        });
    }

    SECTION("Vector-vector addition", "[Vector]")
    {
        rc::check("Vector-vector addition", [](std::array<double, 3> elems1, std::array<double, 3> elems2) {
            Vector<3, double> v1 = Vector{ elems1 };
            Vector<3, double> v2 = Vector{ elems2 };
            auto result = v1 + v2;
            REQUIRE(Utility::equals(v1.at(0) + v2.at(0), result.at(0)));
            REQUIRE(Utility::equals(v1.at(1) + v2.at(1), result.at(1)));
            REQUIRE(Utility::equals(v1.at(2) + v2.at(2), result.at(2)));

            REQUIRE(Utility::equals(v1.at(0) + v2.at(0), result.at(0)));
            REQUIRE(Utility::equals(v1.at(1) + v2.at(1), result.at(1)));
            REQUIRE(Utility::equals(v1.at(2) + v2.at(2), result.at(2)));
        });
    }

    SECTION("Magnitude", "[Vector]")
    {
        Vector<2, int> v{ { 1, 1 } };
        REQUIRE(magnitude(v) == sqrt(2));
    }

    SECTION("Vector dot products", "[Vector]")
    {
        Vector<3, int> vec1{ { 1, 2, 3 } };
        Vector<3, int> vec2{ { 3, 2, 1 } };
        REQUIRE(dot(vec1, vec2) == 10);

        Vector<3, double> g = Vector<3, double>{{0, 2, 1}};

        auto dott = dot(g, g);
        auto magni = magnitude(g) * magnitude(g);

        auto eq = Utility::equals(dott, magni);

        REQUIRE(eq);

        rc::check("Vector-dot product", [](std::array<double, 3> elems1, std::array<double, 3> elems2) {
               Vector<3, double> v1 = Vector{ elems1 };
               Vector<3, double> v2 = Vector{ elems2 };

               REQUIRE(Utility::equals(dot(v1, v2), dot(v2, v1)));
               REQUIRE(Utility::equals(dot(v1, v1), magnitude(v1) * magnitude(v1)));
               REQUIRE(dot(v1, v2) <= magnitude(v1) * magnitude(v2));
        });
    }

    SECTION("Vector cross products", "[Vector]")
    {
        Vector<3, int> vec1{ { 1, 0, 0 } };
        Vector<3, int> vec2{ { 0, 1, 0 } };
        Vector<3, int> result{ { 0, 0, 1 } };

        REQUIRE(cross(vec1, vec2) == result);

        rc::check("Vector cross product", [](std::array<double, 3> elems1, std::array<double, 3> elems2) {
               Vector<3, double> v1 = Vector{ elems1 };
               Vector<3, double> v2 = Vector{ elems2 };

               REQUIRE(cross(v2, v1) == cross(v1, v2).negate());

               auto dcr = dot(cross(v1, v2), v1);
               auto dcr2 = dot(cross(v1, v2), v2);

               REQUIRE(Utility::equals(dcr, 0.0, 1.0)); // floating point tolerance
               REQUIRE(Utility::equals(dcr2, 0.0, 1.0)); // floating point tolerance
        });
    }
}
