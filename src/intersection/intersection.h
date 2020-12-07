//
// Created by Berci on 2020. 12. 06..
//

#ifndef GAME_ENGINE_MATHEMATICS_INTERSECTION_H
#define GAME_ENGINE_MATHEMATICS_INTERSECTION_H

#include <optional>

#include "../Line/Line.h"
#include "../Plane/Plane.h"
#include "../Vector/Vector.h"

namespace GEM {
    std::optional<Vector<4, float>> intersects(const Line& line, const Plane& plane);
}

#endif//GAME_ENGINE_MATHEMATICS_INTERSECTION_H
