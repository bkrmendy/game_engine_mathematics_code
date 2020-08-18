//
// Created by Berci on 2020. 08. 18..
//

#ifndef MYPROJECT_TRANSFORMS_H
#define MYPROJECT_TRANSFORMS_H

#include <cmath>

#include "../Vector/Vector.h"
#include "../Matrix/Matrix.h"
#include "../Utility/Utility.h"

namespace GEM::Transforms {
    Matrix<double, 3, 3> Coordinate(Vector<3, double> u, Vector<3, double> v, Vector<3, double> w) {
        return Matrix<double, 3, 3> {{
            u.at(0), v.at(0), w.at(0),
            u.at(1), v.at(1), w.at(1),
            u.at(2), v.at(2),
        }};
    }

    Matrix<double, 3, 3> Scale(double by) {
        return Matrix<double, 3, 3> {{
                                             by, 0, 0,
                                             0, by, 0,
                                             0, 0, by,
                                     }};
    }

    Matrix<double, 3, 3> Scale(double x, double y, double z) {
        return Matrix<double, 3, 3> {{
                                             x, 0, 0,
                                             0, y, 0,
                                             0, 0, z,
                                     }};
    }

    Matrix<double, 3, 3> Scale(Vector<3, double> u, Vector<3, double> v, Vector<3, double> w, double x, double y, double z) {
        auto coordTransform = Coordinate(u, v, w);
        auto scale = Scale(x, y, z);
        auto inv = inverse(coordTransform);

        assert(inv.has_value());

        return coordTransform * scale * inv.value();
    }

    Matrix<double, 2, 2> Rotation2(Utility::Radian angle) {
        return Matrix<double, 2, 2> {{
            std::cos(angle), -std::sin(angle),
            std::sin(angle), std::cos(angle)
        }};
    }

    Matrix<double, 3, 3> Rotation3Z(Utility::Radian angle) {
        return Matrix<double, 3, 3> {{
           std::cos(angle), -std::sin(angle), 0,
           std::sin(angle), std::cos(angle), 0,
           0, 0, 1
        }};
    }

    Matrix<double, 3, 3> Rotation3X(Utility::Radian angle) {
        return Matrix<double, 3, 3> {{
            1, 0, 0,
             0 ,std::cos(angle), -std::sin(angle),
             0, std::sin(angle), std::cos(angle),
         }};
    }

    Matrix<double, 3, 3> Rotation3Y(Utility::Radian angle) {
        return Matrix<double, 3, 3> {{
                 std::cos(angle), 0, -std::sin(angle),
                 0,1, 0,
                 -std::sin(angle), 0 , std::cos(angle),
         }};
    }

    Matrix<double, 3, 3> Rotation3(Vector<3, double> axis, Utility::Radian angle) {
        auto s = std::sin(angle);
        auto c = std::cos(angle);

        auto a = c + (1 - c) * axis.at(0) * axis.at(0);
        auto b = (1-c) * axis.at(0) * axis.at(1) - s * axis.at(2);
        auto cc = (1-c) * axis.at(0)*axis.at(2) + s*axis.at(1);

        auto d = (1-c) * axis.at(0) * axis.at(1) + s* axis.at(2);
        auto e = c + (1-c) * axis.at(1) * axis.at(1);
        auto f = (1-c) * axis.at(1) * axis.at(2) - s*axis.at(0);

        auto g = (1-c) * axis.at(0) * axis.at(2) - s * axis.at(1);
        auto h = (1-c) * axis.at(1) + axis.at(2) + s*axis.at(0);
        auto i = c + (1-c) * axis.at(2) * axis.at(2);


        return Matrix<double, 3, 3> {{
            a, b, cc,
            d, e, f,
            g, h, i
        }};
    }

}

#endif //MYPROJECT_TRANSFORMS_H
