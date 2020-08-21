//
// Created by Berci on 2020. 08. 13..
//

#include <catch2/catch.hpp>
#include <rapidcheck.h>

#include "../src/Matrix/Matrix.h"
#include "../src/Utility/FloatingPointEquals.h"

using namespace GEM;

TEST_CASE("Matrix operations", "[matrix]") {
    SECTION("Can construct matrix") {
        Matrix<int, 2, 2> mat{{1, 0, 0, 1}};
    }

    SECTION("Can make identity matrix") {
        auto id2x2 = Matrix<int, 2, 2>::Identity();
        auto actualId2x2 = Matrix<int, 2, 2>{{
            1, 0,
            0, 1
        }};

        REQUIRE(id2x2 == actualId2x2);

        auto id3x3 = Matrix<double, 3, 3>::Identity();
        auto actualId3x3 = Matrix<double, 3, 3>{{
                                                     1, 0, 0,
                                                     0, 1, 0,
                                                     0, 0, 1
                                             }};

        REQUIRE(id3x3 == actualId3x3);

        auto id4x4 = Matrix<float, 4, 4>::Identity();
        auto actualId4x4 = Matrix<float, 4, 4>{{
                                    1, 0, 0, 0,
                                    0, 1, 0, 0,
                                    0, 0, 1, 0,
                                    0, 0, 0, 1
                            }};

        REQUIRE(id4x4 == actualId4x4);

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

        rc::check("Matrix transpose applied twice yields original matrix", [](std::array<int, 16> elems) {
           Matrix<int, 4, 4> matrix = Matrix<int, 4, 4>{elems};
           REQUIRE(transposed(transposed(matrix)) == matrix);
        });
    }

    SECTION("Matrix multiplication by scalar") {
        Matrix<double, 2, 3> original{{
                                           1, 2, 3,
                                           4, 5, 6,
                                   }};

        rc::check("Matrix multiplication by scalar",[&original](double scalar) {
            auto result = original * scalar;

            REQUIRE(Utility::equals(result.at(0, 0), original.at(0, 0) * scalar));
            REQUIRE(Utility::equals(result.at(0, 1), original.at(0, 1) * scalar));
            REQUIRE(Utility::equals(result.at(0, 2), original.at(0, 2) * scalar));
            REQUIRE(Utility::equals(result.at(1, 0), original.at(1, 0) * scalar));
            REQUIRE(Utility::equals(result.at(1, 1), original.at(1, 1) * scalar));
            REQUIRE(Utility::equals(result.at(1, 2), original.at(1, 2) * scalar));
        });
    }

    SECTION("Adding scalar to matrix") {
        Matrix<int, 2, 3> original{{
                                           1, 2, 3,
                                           4, 5, 6,
                                   }};

        rc::check("Adding scalar to matrix",[&original](int scalar) {
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

    SECTION("Multiply matrix with vector") {
        SECTION("2x2") {
            auto mat = Matrix<int, 2, 2> {{
                1,2,
                3,4
            }};

            auto vec = Vector<2, int> {{
                5,6
            }};

            auto result = Vector<2, int> {{
                17, 39
            }};

            REQUIRE(mat * vec == result);
        }

        SECTION("3x3") {
            auto mat = Matrix<int, 3, 3> {{
                                                  1,2, 3,
                                                  4,5, 6,
                                                  7,8,9
                                          }};

            auto vec = Vector<3, int> {{
                                               10, 11, 12
                                       }};

            auto result = Vector<3, int> {{
                                                  68, 167, 266
                                          }};

            REQUIRE(mat * vec == result);
        }

        SECTION("4x4") {
            auto mat = Matrix<int, 4,4> {{
                1,2,3,4,
                5,6,7,8,
                9,10,11,12,
                                                 13, 14, 15, 16
            }};

            auto vec = Vector<4, int> {{
                17, 18, 19, 20
            }};

            auto res = Vector<4, int> {{
                                               190, 486, 782, 1078
            }};

            REQUIRE(mat * vec == res);
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

            rc::check("Matrix determinants", [](std::array<double, 4> e1, std::array<double, 4> e2) {
                auto mat1 = Matrix<double, 2,2> {e1};

                auto mat2 = Matrix<double, 2,2>{e2};

                REQUIRE(Utility::equals(determinant(mat1 * mat2), determinant(mat1) * determinant(mat2), 0.0001));
            });
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

            rc::check("Matrix determinants", [](std::array<double, 9> e1, std::array<double, 9> e2) {
                auto matrix1 = Matrix<double, 3, 3> {e1};

                auto matrix2 = Matrix<double, 3, 3> {e2};

                REQUIRE(Utility::equals(determinant(matrix1 * matrix2), determinant(matrix1) * determinant(matrix2), 0.0001));
            });
        }
    }

    SECTION("Inverse") {
        SECTION("2x2") {
            auto matrix2x2 = Matrix<int, 2, 2>{{
                                                       1,2,
                                                       3,4
                                               }};

            auto actualInverse2x2 = Matrix<double, 2, 2>{{
                                                                 -2, 1,
                                                                 1.5, -0.5
                                                         }};

            REQUIRE(is_invertible(matrix2x2));
            REQUIRE(inverse(matrix2x2) == actualInverse2x2);
        }

        SECTION("Properties") {
            auto matrix3x3 = Matrix<double, 3,3> {{
                                                          1,2,3,
                                                          0,1,4,
                                                          5,6,0
                                                  }};

            auto actualInverse3x3 = Matrix<double, 3, 3> {{
                                                                  -24, 18, 5,
                                                                  20, -15, -4,
                                                                  -5, 4, 1
                                                          }};

            REQUIRE(is_invertible(matrix3x3));
            REQUIRE(is_invertible(transposed(matrix3x3)));

            auto result = inverse(matrix3x3);

            REQUIRE(result.has_value());

            REQUIRE(inverse(matrix3x3) == actualInverse3x3);

            REQUIRE(result.value() * matrix3x3 == matrix3x3 * result.value());

            REQUIRE(result.value() * matrix3x3 == Matrix<double, 3, 3>::Identity());

            REQUIRE(matrix3x3 * result.value() == Matrix<double, 3, 3>::Identity());

            auto inverseAgain = inverse(result.value());

            REQUIRE(inverseAgain.has_value());
            REQUIRE(inverseAgain.value() == matrix3x3);
        }

        SECTION("Inverse associativity") {
            auto m1 = Matrix<double, 3,3> {{
                                                          1,2,3,
                                                          0,1,4,
                                                          5,6,0
                                                  }};

            auto m2 = Matrix<double, 3, 3> {{
                                                    0, -3, -2,
                                                    1, -4, -2,
                                                    -3, 4, 1
                                            }};

            REQUIRE(is_invertible(m1));
            REQUIRE(is_invertible(m2));

            auto result1 = inverse(m1);
            auto result2 = inverse(m2);

            auto m1TimesM2 = m1 * m2;

            REQUIRE(is_invertible(m1TimesM2));

            auto resultTimes = inverse(m1TimesM2);

            REQUIRE(resultTimes.has_value());
            REQUIRE(resultTimes.value() == result2.value() * result1.value());
        }
    }
}