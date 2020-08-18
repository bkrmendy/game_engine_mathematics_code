//
// Created by Berci on 2020. 08. 13..
//

#ifndef MYPROJECT_MATRIX_H
#define MYPROJECT_MATRIX_H

#include <type_traits>
#include <array>

namespace GEM {

    template<typename T, size_t N, size_t M, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
    class Matrix {
        std::array<T, N * M> elements_;
    public:
        Matrix(std::array<T, N * M> elements) : elements_{elements} {}

        const T& at(size_t i, size_t j) const {
            assert(i < N);
            assert(j < M);
            return elements_.at(i * M + j);
        }

        T& at(size_t i, size_t j) {
            assert(i < N);
            assert(j < M);
            return elements_.at(i * M + j);
        }
    };

    template<typename T, size_t N, size_t M, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
    bool operator==(const Matrix<float, N, M> &one, const Matrix<float, N, M> &other) {
        bool result = true;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                result = result && equals(one.at(i, j), other.at(i, j));
            }
        }
        return result;
    }

    template<typename T, size_t N, size_t M, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
    bool operator==(const Matrix<T, N, M> &one, const Matrix<T, N, M> &other) {
        bool result = true;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                result = result && one.at(i, j) == other.at(i, j);
            }
        }
        return result;
    }

    template<typename T, size_t N, size_t M, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
    Matrix<T, N, M> operator*(const Matrix<T, N, M>& matrix, const T& scalar) {
        Matrix<T, N, M> result{std::array<T, N * M>{}};
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                result.at(i, j) = matrix.at(i, j) * scalar;
            }
        }
        return result;
    }

    template<typename T, size_t N, size_t M, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
    Matrix<T, N, M> operator+(const Matrix<T, N, M>& matrix, const T& scalar) {
        Matrix<T, N, M> result{std::array<T, N * M>{}};
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                result.at(i, j) = matrix.at(i, j) + scalar;
            }
        }
        return result;
    }

    template<typename T, size_t N, size_t M, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
    Matrix<T, N, M> operator+(const Matrix<T, N, M>& matrix, const Matrix<T, N, M> other) {
        Matrix<T, N, M> result{std::array<T, N * M>{}};
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                result.at(i, j) = matrix.at(i, j) + other.at(i, j);
            }
        }
        return result;
    }

    template<typename T, size_t N, size_t M, size_t K, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
    Matrix<T, N, K> operator*(const Matrix<T, N, M>& matrix, const Matrix<T, M, K> other) {
        Matrix<T, N, K> result{std::array<T, N * K>{}};
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
    Matrix<T, M, N> transposed(const Matrix<T, N, M>& matrix) {
        std::array<T, M * N> transposedElements{};
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                auto elem = matrix.at(i, j);
                transposedElements.at(j * N + i) = elem;
            }
        }
        return Matrix<T, M, N>{transposedElements};
    }

    template<typename T, size_t N, size_t M, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
    bool is_diagonal(const Matrix<float, N, M> &matrix) {
        bool is_diagonal = true;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                is_diagonal = is_diagonal && equals(matrix.at(i, j), 0);
            }
        }
        return is_diagonal;
    }

    template<typename T, size_t N, size_t M, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
    bool is_diagonal(const Matrix<T, N, M>& matrix)  {
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
    
}

#endif //MYPROJECT_MATRIX_H
