//
// Created by Berci on 2020. 08. 13..
//

#ifndef MYPROJECT_MATRIX_H
#define MYPROJECT_MATRIX_H

#include <type_traits>
#include <array>

template <typename T, size_t N, size_t M, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
class Matrix {
    std::array<T, N*M> elements_;
public:
    Matrix(std::array<T, N*M> elements) : elements_{elements} { }

    T at(size_t i, size_t j) const {
        assert(i < N);
        assert(j < M);
        return elements_.at(i * M + j);
    }

    T& at(size_t i, size_t j) {
        assert(i < N);
        assert(j < M);
        return elements_.at(i * M + j);
    }

    bool operator==(const Matrix<T, N, M>& other) const {
        bool result = true;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                result = result && this->at(i, j) == other.at(i, j);
            }
        }
        return result;
    }

    bool diagonal() const {
        bool is_diagonal = true;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                if (i != j) {
                    is_diagonal = is_diagonal && this->at(i, j) == 0;
                }
            }
        }
        return is_diagonal;
    }

    Matrix<T, M, N> transpose() const {
        std::array<T, M*N> transposedElements{};
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                auto elem = this->at(i, j);
                transposedElements.at(j * N + i) = elem;
            }
        }
        return Matrix<T, M, N>(transposedElements);
    }

    void operator*=(T scalar) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                this->at(i, j)*= scalar;
            }
        }
    }

    Matrix<T, N, M> operator*(T scalar) const {
        Matrix<T, N, M> result{std::array<T, N*M>{}};
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                result.at(i, j) = this->at(i, j) * scalar;
            }
        }

        return result;
    }

    void operator+=(T scalar) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                this->at(i, j)+= scalar;
            }
        }
    }

    Matrix<T, N, M> operator+(T scalar) const {
        Matrix<T, N, M> result{std::array<T, N*M>{}};
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                result.at(i, j) = this->at(i, j) + scalar;
            }
        }
        return result;
    }

    Matrix<T, N, M> operator+(const Matrix<T, N, M> other) const {
        Matrix<T, N, M> result{std::array<T, N*M>{}};
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                result.at(i, j) = this->at(i, j) + other.at(i, j);
            }
        }
        return result;
    }

    template <size_t K>
    Matrix<T, N, K> operator*(const Matrix<T, M, K>& other) {
        Matrix<T, N, K> result{std::array<T, N*K>{}};
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < K; ++j) {
                T acc = 0;
                for (size_t k = 0; k < M; ++k) {
                    acc += this->at(i, k) * other.at(k, j);
                }
                result.at(i, j) = acc;
            }
        }
        return result;
    }
};

#endif //MYPROJECT_MATRIX_H
