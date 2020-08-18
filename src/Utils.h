//
// Created by Berci on 2020. 08. 18..
//

#ifndef MYPROJECT_UTILS_H
#define MYPROJECT_UTILS_H

#include <numeric>

bool equals(float a, float b, float epsilon = std::numeric_limits<float>::epsilon()) {
    return fabs(a - b) < epsilon;
}

bool equals(double a, double b, double epsilon = std::numeric_limits<double>::epsilon()) {
    return fabs(a - b) < epsilon;
}

#endif //MYPROJECT_UTILS_H
