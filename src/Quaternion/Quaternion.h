//
// Created by Berci on 2020. 08. 18..
//

#ifndef MYPROJECT_QUATERNION_H
#define MYPROJECT_QUATERNION_H

#include <tuple>
#include <utility>

#include "../Vector/Vector.h"

namespace GEM {
    class Quaternion {
        double scalar_;
        std::tuple<double, double, double> components_;
    public:
        Quaternion(double scalar, std::tuple<double, double, double> components) : scalar_{scalar}, components_{std::move(components)} { }
        const double& scalar() const { return this->scalar_; }
        const double& i() const { return std::get<0>(this->components_); }
        const double& j() const { return std::get<1>(this->components_); }
        const double& k() const { return std::get<2>(this->components_); }

        Quaternion conjugate() const {
            return Quaternion(scalar_, std::tuple{-this->i(), -this->j(), -this->k()});
        }


    };

    Quaternion operator*(const Quaternion& one, const Quaternion& other) {
        
        auto scalarPart = one.scalar() * other.scalar()
    }
}

#endif //MYPROJECT_QUATERNION_H
