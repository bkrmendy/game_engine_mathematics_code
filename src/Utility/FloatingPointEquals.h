//
// Created by Berci on 2020. 08. 18..
//

#ifndef MYPROJECT_FLOATINGPOINTEQUALS_H
#define MYPROJECT_FLOATINGPOINTEQUALS_H

#include <numeric>
#include <cmath>

namespace GEM::Utility {
    template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
    bool equals(T a, T b, T epsilon = std::numeric_limits<T>::epsilon()) {
        return std::abs(a - b) < epsilon;
    }
}

#endif //MYPROJECT_FLOATINGPOINTEQUALS_H
