//
// Created by Berci on 2020. 08. 13..
//

#include <catch2/catch.hpp>
#include <rapidcheck.h>

#include "../src/Matrix/Matrix.h"
#include "../src/Utils.h"

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

    SECTION("Matrix diagonal") {
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

    SECTION("Matrix transpose") {
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

        Matrix<double, 2, 3> original{{
                                           1, 2, 3,
                                           4, 5, 6,
                                   }};

        rc::check("Matrix multiplication by scalar",[&original](double scalar) {
            auto result = original * scalar;

            REQUIRE(equals(result.at(0, 0), original.at(0, 0) * scalar));
            REQUIRE(equals(result.at(0, 1), original.at(0, 1) * scalar));
            REQUIRE(equals(result.at(0, 2), original.at(0, 2) * scalar));
            REQUIRE(equals(result.at(1, 0), original.at(1, 0) * scalar));
            REQUIRE(equals(result.at(1, 1), original.at(1, 1) * scalar));
            REQUIRE(equals(result.at(1, 2), original.at(1, 2) * scalar));
        });
    }

    SECTION("Adding scalar to matrix") {
        Matrix<int, 2, 3> original{{
                                           1, 2, 3,
                                           4, 5, 6,
                                   }};

        rc::check("Matrix multiplication by scalar",[&original](int scalar) {
            auto result = original + scalar;

            REQUIRE(result.at(0, 0) == original.at(0, 0) + scalar);
            REQUIRE(result.at(0, 1) == original.at(0, 1) + scalar);
            REQUIRE(result.at(0, 2) == original.at(0, 2) + scalar);
            REQUIRE(result.at(1, 0) == original.at(1, 0) + scalar);
            REQUIRE(result.at(1, 1) == original.at(1, 1) + scalar);
            REQUIRE(result.at(1, 2) == original.at(1, 2) + scalar);
        });
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

    SECTION("Submatrix", "[Matrix]") {
        auto matrix = Matrix<int, 3, 3> {{
                                                 1,2,3,
                                                 4,5,6,
                                                 7, 8, 9
                                         }};

        auto submatrix1 = submatrix(matrix, 0, 0);

        auto actualSubmatrix1 = Matrix<int, 2, 2>{{
                                                          5,6,
                                                          8,9
                                                  }};

        REQUIRE(submatrix1 == actualSubmatrix1);

        auto submatrix2 = submatrix(matrix, 1, 1);

        auto actualSubmatrix2 = Matrix<int, 2, 2>{{
                                                          1, 3,
                                                          7, 9
                                                  }};

        REQUIRE(submatrix2 == actualSubmatrix2);

        auto submatrix3 = submatrix(matrix, 2, 2);

        auto actualSubmatrix3 = Matrix<int, 2, 2> {{
                                                           1, 2,
                                                           4, 5
                                                   }};

        REQUIRE(submatrix3 == actualSubmatrix3);
    }

    SECTION("Determinant", "[Matrix]") {
        SECTION("2x2") {
            auto matrix = Matrix<int, 2, 2>{{
                                                       1,2,
                                                       3,4
                                               }};

            REQUIRE(determinant(matrix) == -2);

            auto matrixRowsExchanged = Matrix<int, 2, 2> {{
                                                                     3,4,
                                                                     1,2
                                                             }};

            REQUIRE(determinant(matrixRowsExchanged) == -determinant(matrix));

            auto matrixRowsMultiplied = Matrix<int, 2, 2> {{
                                                                      2,4,
                                                                      3,4
                                                              }};

            REQUIRE(determinant(matrixRowsMultiplied) == determinant(matrix) * 2);

            auto matrixIdenticalRows = Matrix<int, 2, 2> {{
                                                                     1,2,
                                                                     1,2
                                                             }};

            REQUIRE(determinant(matrixIdenticalRows) == 0);
        }

        SECTION("4x4") {
            auto matrix = Matrix<int, 4, 4> {{
                                                        1,12,3,14,
                                                        5,6,7,8,
                                                        9, 10, 11, 12,
                                                        13, 14, 15, 17
                                                }};

            REQUIRE(determinant(matrix) == 80);

            auto matrixRowsExchanged = Matrix<int, 4, 4> {{
                                                                     1,12,3,14,
                                                                     9, 10, 11, 12,
                                                                     5,6,7,8,
                                                                     13, 14, 15, 17
                                                             }};

            REQUIRE(determinant(matrixRowsExchanged) == -determinant(matrix));

            auto matrixIdenticalRows = Matrix<int, 4, 4> {{
                                                                     1,12,3,14,
                                                                     1,12,3,14,
                                                                     5,6,7,8,
                                                                     13, 14, 15, 17
                                                             }};

            REQUIRE(determinant(matrixIdenticalRows) == 0);
        }
    }
}