//
// Created by Berci on 2020. 08. 13..
//

#ifndef MYPROJECT_MATRIX_H
#define MYPROJECT_MATRIX_H

#include <type_traits>
#include <array>
#include <cmath>
#include <optional>

#include "../Vector/Vector.h"

#include "../Utility/FloatingPointEquals.h"

namespace GEM {

template<typename T, size_t N, size_t M, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
class Matrix
{
    std::array<T, N * M> elements_;

  public:
    static Matrix<T, N, N> Identity()
    {
        auto result = Matrix<T, N, N>{};
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                if (i == j) {
                    result.at(i, j) = 1;
                } else {
                    result.at(i, j) = 0;
                }
            }
        }
        return result;
    }

    Matrix() : elements_{ std::array<T, N * M>{} } {}
    Matrix(std::array<T, N * M> elements) : elements_{ elements } {}

    T &at(size_t i, size_t j)
    {
        assert(i < N);
        assert(j < M);
        return elements_.at(i * M + j);
    }

    const T &at(size_t i, size_t j) const
    {
        assert(i < N);
        assert(j < M);
        return elements_.at(i * M + j);
    }
};

template<typename T, size_t N, size_t M, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
bool operator==(const Matrix<T, N, M> &one, const Matrix<T, N, M> &other)
{
    bool result = true;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            if constexpr (std::is_floating_point<T>::value) {
                T tolerance = static_cast<T>(0.0000001);
                result = result && Utility::equals(one.at(i, j), other.at(i, j), tolerance);
            } else {
                result = result && one.at(i, j) == other.at(i, j);
            }
        }
    }
    return result;
}

template<typename T, size_t N, size_t M, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
Matrix<T, N, M> operator*(const Matrix<T, N, M> &matrix, const T &scalar)
{
    Matrix<T, N, M> result{};
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            result.at(i, j) = matrix.at(i, j) * scalar;
        }
    }
    return result;
}

template<typename T, size_t N, size_t M, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
Matrix<T, N, M> operator+(const Matrix<T, N, M> &matrix, const T &scalar)
{
    Matrix<T, N, M> result{};
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            result.at(i, j) = matrix.at(i, j) + scalar;
        }
    }
    return result;
}

template<typename T, size_t N, size_t M, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
Matrix<T, N, M> operator+(const Matrix<T, N, M> &matrix, const Matrix<T, N, M> other)
{
    Matrix<T, N, M> result{};
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            result.at(i, j) = matrix.at(i, j) + other.at(i, j);
        }
    }
    return result;
}

template<typename T, size_t N, size_t M, size_t K, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
Matrix<T, N, K> operator*(const Matrix<T, N, M> &matrix, const Matrix<T, M, K> other)
{
    Matrix<T, N, K> result{};
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < K; ++j) {
            T acc = 0;
            for (size_t k = 0; k < M; ++k) {
                acc += matrix.at(i, k) * other.at(k, j);
            }
            result.at(i, j) = acc;
        }
    }
    return result;
}

template<typename T, size_t N, size_t M, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
Vector<N, T> operator*(const Matrix<T, N, M> matrix, const Vector<M, T> &vector)
{
    Vector<N, T> result{};

    for (size_t i = 0; i < N; ++i) {
        T acc = 0;
        for (size_t j = 0; j < M; ++j) {
            acc += matrix.at(i, j) * vector.at(j);
        }
        result.at(i) = acc;
    }

    return result;
}

template<typename T, size_t N, size_t M, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
Matrix<T, M, N> transposed(const Matrix<T, N, M> &matrix)
{
    Matrix<T, M, N> result{};
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            auto elem = matrix.at(i, j);
            result.at(j, i) = elem;
        }
    }
    return result;
}

template<typename T, size_t N, size_t M, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
bool is_diagonal(const Matrix<float, N, M> &matrix)
{
    bool is_diagonal = true;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            is_diagonal = is_diagonal && equals(matrix.at(i, j), 0);
        }
    }
    return is_diagonal;
}

template<typename T, size_t N, size_t M, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
bool is_diagonal(const Matrix<T, N, M> &matrix)
{
    bool is_diagonal = true;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            if (i != j) {
                is_diagonal = is_diagonal && matrix.at(i, j) == 0;
            }
        }
    }
    return is_diagonal;
}

template<typename T, size_t N, size_t M, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
Matrix<T, N - 1, M - 1> submatrix(const Matrix<T, N, M> &matrix, size_t ri, size_t rj)
{
    assert(N > 1);
    assert(M > 1);

    assert(ri < N);
    assert(rj < M);

    Matrix<T, N - 1, M - 1> result{};

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            if (i != ri && j != rj) {
                size_t destinationI = i > ri ? i - 1 : i;
                size_t destinationJ = j > rj ? j - 1 : j;
                result.at(destinationI, destinationJ) = matrix.at(i, j);
            }
        }
    }

    return result;
}

template<typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
double determinant(const Matrix<T, 2, 2> &matrix)
{
    return matrix.at(0, 0) * matrix.at(1, 1) - matrix.at(0, 1) * matrix.at(1, 0);
}

template<typename T, size_t N, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
double determinant(const Matrix<T, N, N> &matrix)
{
    double acc = 0;
    const size_t k = 1;
    for (size_t n = 0; n < N; ++n) {
        auto cofactor = std::pow(-1, n + k) * determinant(submatrix(matrix, n, k));
        acc += matrix.at(n, k) * cofactor;
    }

    return acc;
}

template<typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
std::optional<Matrix<double, 2, 2>> inverse(const Matrix<T, 2, 2> &matrix)
{
    auto det = determinant(matrix);
    if (Utility::equals(det, 0.0)) {
        return std::nullopt;
    }

    auto a = static_cast<double>(matrix.at(0, 0));
    auto b = static_cast<double>(matrix.at(0, 1));
    auto c = static_cast<double>(matrix.at(1, 0));
    auto d = static_cast<double>(matrix.at(1, 1));

    auto result = Matrix<double, 2, 2>{ { d, -b, -c, a } };
    return result * (1 / det);
}

template<typename T, size_t N, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
std::optional<Matrix<double, N, N>> inverse(const Matrix<T, N, N> &matrix)
{
    auto det = determinant(matrix);
    if (Utility::equals(det, 0.0)) {
        return std::nullopt;
    }

    auto result = Matrix<double, N, N>{};
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            auto cofactor = std::pow(-1, i + j) * determinant(submatrix(matrix, j, i));
            result.at(i, j) = cofactor / det;
        }
    }
    return result;
}

template<typename T, size_t N, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
bool is_invertible(const Matrix<T, N, N> &matrix)
{
    return !Utility::equals(determinant(matrix), 0.0);
}

template<typename T, size_t N, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
Matrix<T, 4, 4> asHomogenous(const Matrix<T, 3, 3> &matrix)
{
    return Matrix<T, 4, 4>{ { matrix.at(0, 0), matrix.at(0, 1), matrix.at(0, 2), 0, matrix.at(1, 0), matrix.at(1, 1), matrix.at(1, 2), 0, matrix.at(2, 0), matrix.at(2, 1), matrix.at(2, 2), 0, 0, 0, 0, 1 } };
}

}// namespace GEM

#endif//MYPROJECT_MATRIX_H
