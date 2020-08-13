#include <catch2/catch.hpp>

#include <vector>
#include <type_traits>
#include <random>
#include <rapidcheck.h>

#include "../src/Vector/Vector.h"

template <size_t N, typename T>
Vector<N, T> scalarAdd(const Vector<N, T>& v1, const T& scalar) {
    return v1 + scalar;

}

template <size_t N, typename T>
T dotProduct(const Vector<N, T>& v1, const Vector<N, T>& v2) {
    return v1.dot(v2);
}

TEST_CASE("Vector operations", "[Vectors]")
{
    SECTION("Vector negation", "[Vector]") {
        Vector<3, int> v1{{1,2,3}};
        auto negated = v1.negate();

        for(size_t i = 0; i < 3; ++i) {
            REQUIRE(v1.at(i) + negated.at(i) == 0);
        }
    }

    SECTION("Vector scalar addition", "[Vector]") {
        rc::check("Vector scalar addition", [](const int scalar) {
            Vector<3, int> v1{{1, 2, 3}};
            auto result = scalarAdd(v1, scalar);
            for (size_t i = 0; i < 3; ++i) {
                REQUIRE(result.at(i) - scalar == v1.at(i));
            }
        });
    }

    SECTION("Vector scalar +=", "[Vector]") {
        std::array<int, 3> backer = {3, 2, 1};
        rc::check("Vector scalar in-place addition", [&backer](const int scalar) {
            Vector<3, int> v2{backer};
            v2 += scalar;
            for (size_t i = 0; i < 3; ++i) {
                REQUIRE(v2.at(i) == backer.at(i) + scalar);
            }
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
        REQUIRE(v.magnitude() == sqrt(2));
    }

    SECTION("Vector dot products", "[Vector]") {
        Vector<3, int> v1{{1,2,3}};
        Vector<3, int> v2{{3,2,1}};
        REQUIRE(dotProduct(v1, v2) == 10);
        REQUIRE(dotProduct(v1, v2) == dotProduct(v2, v1));
        REQUIRE(dotProduct(v1, v1) == v1.magnitude() * v1.magnitude());
        REQUIRE(dotProduct(v1, v2) <= v1.magnitude() * v2.magnitude());
    }

    SECTION("Vector cross products", "[Vector]") {
        Vector<3, int> v1{{1,0,0}};
        Vector<3, int> v2{{0,1,0}};
        Vector<3, int> result{{0,0,1}};

        REQUIRE(cross(v1, v2) == result);
        REQUIRE(cross(v2, v1) == result.negate());
        REQUIRE(cross(v1, v2).dot(v1) == 0);
        REQUIRE(cross(v1, v2).dot(v2) == 0);
    }
}
