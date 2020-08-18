//
// Created by Berci on 2020. 08. 18..
//

#ifndef MYPROJECT_UTILS_H
#define MYPROJECT_UTILS_H

#include <numeric>

template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
bool equals(T a, T b, T epsilon = std::numeric_limits<T>::epsilon()) {
    return fabs(a - b) < epsilon;
}

#endif //MYPROJECT_UTILS_H
