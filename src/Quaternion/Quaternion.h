//
// Created by Berci on 2020. 08. 18..
//

#ifndef MYPROJECT_QUATERNION_H
#define MYPROJECT_QUATERNION_H

#include <cmath>
#include <utility>

#include "../Vector/Vector.h"
#include "../Matrix/Matrix.h"
#include "../Utility/Utility.h"


namespace GEM {
    template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
    class Quaternion {
        T scalar_;
        Vector<3, T> components_;
    public:
        Quaternion(const T& scalar, const Vector<3, T>& components) : scalar_{scalar}, components_{components} { }

        static Quaternion ThroughAngleAboutAxis(const Utility::Radian& angle, const Vector<3, T>& axis) {
            return Quaternion{std::cos(angle / 2.0), axis * std::sin(angle / 2.0)};

        }

        const T& real() const {
            return this->scalar_;
        }

        const Vector<3, T>& imag() const {
            return this->components_;
        }

        Quaternion conjugate() const {
            return Quaternion(scalar_, components_.negate());
        }

        T magnitude() const  {
            return std::sqrt(
                    scalar_ * scalar_
            + components_.at(0) * components_.at(0)
            + components_.at(1) * components_.at(1)
            + components_.at(2) * components_.at(2));
        }

        Quaternion inverse() const  {
            auto norm = magnitude();
            return conjugate() / (norm * norm);
        }

        Quaternion normalize() const {
            auto norm = magnitude();
            return Quaternion{ scalar_ / norm, components_ / norm };
        }

        Matrix<T, 3, 3> asMatrix3() const {
            assert(Utility::equals(magnitude(), 1.0));
            auto x = scalar_;
            auto y = components_.at(0);
            auto z = components_.at(1);
            auto w = components_.at(2);

            return Matrix<T, 3, 3> {{
                1 - 2*y*y - 2*z*z, 2*x*y - 2*w*z, 2*x*z + 2*w*y,
                2*x*y + 2*w*z, 1 - 2*x*x - 2*z*z, 2*y*z - 2*w*x,
                2*x*z - 2*w*y, 2*y*z - 2*w*x, 1 - 2*x*x - 2*y*y
            }};
        }
    };

    template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
    Quaternion<T> operator*(const Quaternion<T>& quaternion, const T& scalar) {
        return Quaternion(quaternion.real() * scalar, quaternion.imag() * scalar);
    }

    template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
    Quaternion<T> operator+(const Quaternion<T>& one, const Quaternion<T>& other) {
        return Quaternion<T>{one.real() + other.real(), one.imag() + other.imag()};
    }

    template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
    Quaternion<T> operator*(const Quaternion<T>& one, const Quaternion<T>& other) {
        auto scalarPart = one.real() * other.real() - dot(one.imag(), other.imag());
        auto imaginaryPart = other.imag() * one.real() + one.imag() * other.real() + cross(one.imag(), other.imag());
        return Quaternion(scalarPart, imaginaryPart);
    }
}

#endif //MYPROJECT_QUATERNION_H
