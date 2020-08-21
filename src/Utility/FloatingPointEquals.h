//
// Created by Berci on 2020. 08. 18..
//

#ifndef MYPROJECT_FLOATINGPOINTEQUALS_H
#define MYPROJECT_FLOATINGPOINTEQUALS_H

#include <numeric>
#include <cmath>

namespace GEM::Utility {
// https://stackoverflow.com/a/15012792
template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
bool equals(const T &a, const T &b, T epsilon = std::numeric_limits<T>::epsilon())
{
    double maxAB = std::max({ 1.0, std::fabs(a), std::fabs(b) });
    auto res = std::fabs(a - b) <= epsilon * maxAB;
    return res;
}
}// namespace GEM::Utility

// namespace GEM::Utility

#endif//MYPROJECT_FLOATINGPOINTEQUALS_H
