//
// Created by Berci on 2020. 08. 13..
//

#include <catch2/catch.hpp>

#include "../src/Matrix/Matrix.h"

using namespace GEM;

TEST_CASE("Matrix operations", "[matrix]") {
    SECTION("Can construct matrix") {
        Matrix<int, 2, 2> mat{{1, 0, 0, 1}};
    }

    SECTION("Can access matrix properly") {
        Matrix<int, 2, 2> mat{{1, 2, 3, 4}};
        REQUIRE(mat.at(0, 0) == 1);
        REQUIRE(mat.at(0, 1) == 2);
        REQUIRE(mat.at(1, 0) == 3);
        REQUIRE(mat.at(1, 1) == 4);

        Matrix<int, 2, 3> original{{
                                           1, 2, 3,
                                           4, 5, 6,
                                   }};

        REQUIRE(original.at(0, 0) == 1);
        REQUIRE(original.at(0, 1) == 2);
        REQUIRE(original.at(0, 2) == 3);
        REQUIRE(original.at(1, 0) == 4);
        REQUIRE(original.at(1, 1) == 5);
        REQUIRE(original.at(1, 2) == 6);
    }

    SECTION("Matrix::diagonal") {
        Matrix<int, 3, 3> diagonal{{
            1, 0, 0,
            0, 1, 0,
            0, 0, 1
        }};

        REQUIRE(is_diagonal(diagonal));

        Matrix<int, 3, 3> not_diagonal{{
                                           1, 0, 1,
                                           0, 1, 0,
                                           0, 0, 1
                                   }};

        REQUIRE(!is_diagonal(not_diagonal));
    }

    SECTION("Matrix::transpose") {
        Matrix<int, 2, 3> original{{
                                           1, 2, 3,
                                           4, 5, 6,
                                   }};
        Matrix<int, 3, 2> result {{
            1, 4,
            2, 5,
            3,6
        }};

        const Matrix<int, 3, 2> actualResult = transposed(original);

        REQUIRE(actualResult == result);
    }

    SECTION("Matrix multiplication by scalar") {
        Matrix<int, 2, 3> original{{
                                           1, 2, 3,
                                           4, 5, 6,
                                   }};

        const int scalar = 2;

        auto result = original * scalar;

        REQUIRE(result.at(0, 0) / scalar == 1);
        REQUIRE(result.at(0, 1) / scalar == 2);
        REQUIRE(result.at(0, 2) / scalar == 3);
        REQUIRE(result.at(1, 0) / scalar == 4);
        REQUIRE(result.at(1, 1) / scalar == 5);
        REQUIRE(result.at(1, 2) / scalar == 6);
    }

    SECTION("Adding scalar to matrix") {
        Matrix<int, 2, 3> original{{
                                           1, 2, 3,
                                           4, 5, 6,
                                   }};

        const int scalar = 2;

        auto result = original + scalar;

        REQUIRE(result.at(0, 0) == 3);
        REQUIRE(result.at(0, 1) == 4);
        REQUIRE(result.at(0, 2) == 5);
        REQUIRE(result.at(1, 0) == 6);
        REQUIRE(result.at(1, 1) == 7);
        REQUIRE(result.at(1, 2) == 8);
    }

    SECTION("Adding matrix to matrix") {
        Matrix<int, 2, 3> m1{{
                                           1, 2, 3,
                                           4, 5, 6,
                                   }};

        Matrix<int, 2, 3> m2{{
                                           2, 3, 4,
                                           5, 6, 7,
                                   }};

        auto result = m1 + m2;

        auto realResult = Matrix<int, 2, 3>{{
            3, 5, 7,
            9, 11, 13
        }};

        REQUIRE(result == realResult);
    }

    SECTION("Multiply matrix by matrix") {
        SECTION("NxN matrices") {
            auto m1 = Matrix<int, 2, 2>{{
                                                1,2,
                                                3,4
                                        }};

            auto m2 = Matrix<int, 2, 2>{{
                                                5, 6,
                                                7, 8
                                        }};

            auto result = m1 * m2;

            auto realResult = Matrix<int, 2, 2>{{
                                                        19, 22,
                                                        43, 50

                                                }};

            REQUIRE(result == realResult);
        }

        SECTION("Matrices with non-equal dimensions") {
            auto m3 = Matrix<int, 2, 3>{{
                                                1, 2, 3,
                                                4, 5, 6,
                                        }};

            auto m4 = Matrix<int, 3, 4>{{
                                                1, 2, 3,4,
                                                5, 6,7, 8,
                                                9,10, 11, 12
                                        }};

            auto result = m3 * m4;

            auto actualResult = Matrix<int, 2, 4>{{
                38, 44, 50, 56,
                83, 98, 113, 128
            }};

            REQUIRE(result == actualResult);
        }
    }
}