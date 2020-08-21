#include <catch2/catch.hpp>

#include <vector>
#include <type_traits>
#include <random>
#include <rapidcheck.h>

#include "../src/Vector/Vector.h"
#include "../src/Utility/FloatingPointEquals.h"

using namespace GEM;

TEST_CASE("Vector operations", "[Vectors]")
{
    SECTION("Vector negation", "[Vector]") {
        Vector<3, int> v1{{1,2,3}};
        auto negated = v1.negate();

        for(size_t i = 0; i < 3; ++i) {
            REQUIRE(v1.at(i) + negated.at(i) == 0);
        }
    }

    SECTION("Vector-scalar addition", "[Vector]") {
        Vector<3, int> v1{{1, 2, 3}};
        rc::check("Vector scalar addition", [&v1](const int scalar) {
            auto result = v1 + scalar;
            REQUIRE(result.at(0) == v1.at(0) + scalar);
            REQUIRE(result.at(1) == v1.at(1) + scalar);
            REQUIRE(result.at(2) == v1.at(2) + scalar);
        });
    }

    SECTION("Vector-scalar multiplication", "[Vector]") {
        Vector<3, int> v1{{1, 2, 3}};
        rc::check("Vector-scalar multiplication", [&v1](const int scalar) {
            auto result = v1 * scalar;
            REQUIRE(result.at(0) == v1.at(0) * scalar);
            REQUIRE(result.at(1) == v1.at(1) * scalar);
            REQUIRE(result.at(2) == v1.at(2) * scalar);
        });
    }

    SECTION("Vector-scalar division", "[Vector]") {
        Vector<3, double> v1{{1, 2, 3}};
        rc::check("Vector-scalar division", [&v1](const double scalar) {
            RC_PRE(!Utility::equals(scalar, 0.0));

            auto result = v1 / scalar;
            REQUIRE(result.at(0) == v1.at(0) / scalar);
            REQUIRE(result.at(1) == v1.at(1) / scalar);
            REQUIRE(result.at(2) == v1.at(2) / scalar);
        });
    }

    SECTION("Vector-vector addition", "[Vector]") {
        Vector<3, int> v1{{1,2,3}};
        Vector<3, int> v2{{3,2,1}};
        Vector<3, int> v3{{1,1,1}};
        Vector<3, int> result{{4,4,4}};
        REQUIRE(v1 + v2 == result);
        REQUIRE(v1 + v2 == v2 + v1);
        REQUIRE(v1 + v3 != v2);
    }

    SECTION("Magnitude", "[Vector]") {
        Vector<2, int> v{{1, 1}};
        REQUIRE(magnitude(v) == sqrt(2));
    }

    SECTION("Vector dot products", "[Vector]") {
        Vector<3, int> v1{{1,2,3}};
        Vector<3, int> v2{{3,2,1}};
        REQUIRE(dot(v1, v2) == 10);
        REQUIRE(dot(v1, v2) == dot(v2, v1));
        REQUIRE(dot(v1, v1) == magnitude(v1) * magnitude(v1));
        REQUIRE(dot(v1, v2) <= magnitude(v1) * magnitude(v2));
    }

    SECTION("Vector cross products", "[Vector]") {
        Vector<3, int> v1{{1,0,0}};
        Vector<3, int> v2{{0,1,0}};
        Vector<3, int> result{{0,0,1}};

        REQUIRE(cross(v1, v2) == result);
        REQUIRE(cross(v2, v1) == result.negate());
        REQUIRE(dot(cross(v1, v2), v1) == 0);
        REQUIRE(dot(cross(v1, v2), v2) == 0);
    }
}
