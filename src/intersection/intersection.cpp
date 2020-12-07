//
// Created by Berci on 2020. 12. 06..
//

#include "./intersection.h"
#include "../Utility/FloatingPointEquals.h"

namespace GEM {
    std::optional<Vector<4, float>> intersects(const Line& line, const Plane& plane) {
        const float denom = dot(plane.hypernormal(), line.direction());
        if (Utility::equals<float>(denom, 0)) {
            return std::nullopt;
        }

        const auto t = - (dot(plane.hypernormal(), line.origin()) / denom);

        return point_along_line(line, t);
    }
}