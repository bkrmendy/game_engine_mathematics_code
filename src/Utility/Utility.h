//
// Created by Berci on 2020. 08. 18..
//

#ifndef MYPROJECT_UTILITY_H
#define MYPROJECT_UTILITY_H

namespace GEM::Utility {
    struct Radian {
        double radians;
        Radian(double radians) : radians{radians} { }

        operator double() const {
            return radians;
        }
    };
}

#endif //MYPROJECT_UTILITY_H
