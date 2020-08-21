//
// Created by Berci on 2020. 08. 11..
//

#ifndef MYPROJECT_VECTOR_H
#define MYPROJECT_VECTOR_H

#include <type_traits>
#include <array>
#include <algorithm>
#include <cmath>

#include "../Utility/FloatingPointEquals.h"

namespace GEM {

    template<size_t N, typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
    class Vector {
        std::array<T, N> elems_;
    public:
        Vector() : elems_{std::array<T, N>{}} { }
        explicit Vector(std::array<T, N> elems) : elems_{elems} { };

        T& at(size_t idx) {
            assert(idx < N);
            return elems_.at(idx);
        }

        const T& at(size_t idx) const {
            assert(idx < N);
            return elems_.at(idx);
        }

        Vector<N, T> negate() const {
            std::array<T, N> elems{};
            for (size_t i = 0; i < N; ++i) {
                elems.at(i) = -1 * this->at(i);
            }
            return Vector(elems);
        }
    };

    template<typename T, size_t N, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
    bool operator==(const Vector<N, T> &one, const Vector<N, T> &other) {
        auto result = true;
        for (size_t i = 0; i < N; ++i) {
            if constexpr (std::is_floating_point<T>::value) {
                result = result && Utility::equals(one.at(i), other.at(i));
            } else {
                result = result && (one.at(i) == other.at(i));
            }
        }
        return result;
    }

    template<typename T, size_t N, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
    bool operator!=(const Vector<N, T> &one, const Vector<N, T> &other) {
        return !(one == other);
    }

    template<typename T, size_t N, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
    Vector<N, T> operator+(const Vector<N, T>& vector, const T &scalar) {
        std::array<T, N> elems{};
        for (size_t i = 0; i < N; ++i) {
            elems.at(i) = vector.at(i) + scalar;
        }
        return Vector(elems);
    }

    template<typename T, size_t N, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
    Vector<N, T> operator+(const Vector<N, T>& vector, const Vector<N, T> &other) {
        std::array<T, N> elems{};
        for (size_t i = 0; i < N; ++i) {
            elems.at(i) = vector.at(i) + other.at(i);
        }
        return Vector(elems);
    }

    template<typename T, size_t N, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
    Vector<N, T> operator*(const Vector<N, T>& vector, const T& scalar) {
        std::array<T, N> elems{};
        for (size_t i = 0; i < N; ++i) {
            elems.at(i) = vector.at(i) * scalar;
        }
        return Vector(elems);
    }

    template<typename T, size_t N, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
    Vector<N, T> operator/(const Vector<N, T>& vector, const T& scalar) {
        assert(scalar != 0.0);
        std::array<T, N> elems{};
        for (size_t i = 0; i < N; ++i) {
            elems.at(i) = vector.at(i) / scalar;
        }
        return Vector(elems);
    }

    template<typename T, size_t N, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
    double magnitude(const Vector<N, T> &vector) {
        double result = 0;
        for (size_t t = 0; t < N; ++t) {
            result += vector.at(t) * vector.at(t);
        }
        return std::sqrt(result);
    }

    template<typename T, size_t N, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
    T dot(const Vector<N, T> &vector, const Vector<N, T> &other) {
        T result = 0;
        for (size_t t = 0; t < N; ++t) {
            result += vector.at(t) * other.at(t);
        }
        return result;
    }

    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = nullptr>
    Vector<3, T> cross(const Vector<3, T> &p, const Vector<3, T> &q) {
        return Vector<3, T>{{
                                    p.at(1) * q.at(2) - p.at(2) * q.at(1),
                                    p.at(2) * q.at(0) - p.at(0) * q.at(2),
                                    p.at(0) * q.at(1) - p.at(1) * q.at(0)
                            }};
    }
}

#endif //MYPROJECT_VECTOR_H
