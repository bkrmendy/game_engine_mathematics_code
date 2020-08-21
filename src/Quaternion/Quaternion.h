//
// Created by Berci on 2020. 08. 18..
//

#ifndef MYPROJECT_QUATERNION_H
#define MYPROJECT_QUATERNION_H

#include <cmath>
#include <utility>

#include "../Vector/Vector.h"
#include "../Utility/Utility.h"

namespace GEM {
    class Quaternion {
        double scalar_;
        Vector<3, double> components_;
    public:
        Quaternion(const double& scalar, const Vector<3, double>& components) : scalar_{scalar}, components_{components} { }

        static Quaternion throughAngleAboutAxis(const Utility::Radian& angle, const Vector<3, double>& axis) {
            return Quaternion{
                std::cos(static_cast<double>(angle) / 2),
                axis * std::sin(static_cast<double>(angle) / 2)
            };

        }

        const double& scalar() const { return this->scalar_; }
        const double& i() const { return this->components_.at(0); }
        const double& j() const { return this->components_.at(1); }
        const double& k() const { return this->components_.at(2); }

        Quaternion conjugate() const {
            return Quaternion(scalar_, this->components_.negate());
        }
    };

    Quaternion operator*(const Quaternion& one, const Quaternion& other) {
        auto scalarPart = one.scalar() * other.scalar();

    }
}

#endif //MYPROJECT_QUATERNION_H
