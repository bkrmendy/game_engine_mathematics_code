//
// Created by Berci on 2020. 08. 11..
//

#ifndef MYPROJECT_VECTOR_H
#define MYPROJECT_VECTOR_H

#include <type_traits>
#include <array>

template <unsigned int N, typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
class Vector {
    std::array<T, N> elems_;
public:
    explicit Vector(std::array<T, N> elems) : elems_{elems} { };

    T at(size_t idx) const {
        assert(idx < N);
        return elems_.at(idx);
    }

    bool operator==(const Vector<N, T>& other) const {
        auto result = true;
        for (size_t i = 0; i < N; ++i) {
            result = result && (elems_.at(i) == other.at(i));
        }
        return result;
    }

    bool operator !=(const Vector<N, T>& other) const {
        return !(*this == other);
    }

    void operator+=(const T& scalar) {
        for (auto& elem : elems_) {
            elem += scalar;
        }
    }

    Vector<N, T> operator+(const T& scalar) const {
        auto newElems = elems_;
        for (auto& elem : newElems) {
            elem += scalar;
        }
        return Vector<N, T>(newElems);
    }

    void operator +=(const Vector<N, T>& other) {
        for (size_t i = 0; i < N; ++i) {
            elems_.at() += other.at(i);
        }
    }

    Vector<N, T> operator+(const Vector<N, T>& other) const {
        std::array<T, N> elems{};
        for (size_t i = 0; i < N; ++i) {
            elems.at(i) = this->at(i) + other.at(i);
        }
        return Vector(elems);
    }

    void operator *=(const T& scalar) {
        for (auto& elem : elems_) {
            elem *= scalar;
        }
    }

    Vector<N, T> operator * (const T& scalar) const  {
        auto newElems = elems_;
        for (auto& elem : newElems) {
            elem *= scalar;
        }
        return Vector<N, T>(newElems);
    }

    double magnitude() const {
        double result = 0;
        for (auto elem : elems_) {
            result += elem * elem;
        }
        return sqrt(result);
    }

    T dot(const Vector<N, T>& other) const {
        T result = 0;
        for (size_t t = 0; t < N; ++t) {
            result += this->at(t) * other.at(t);
        }
        return result;
    }
};


#endif //MYPROJECT_VECTOR_H