//
// Created by Berci on 2020. 12. 05..
//

#ifndef GAME_ENGINE_MATHEMATICS_PLANE_H
#define GAME_ENGINE_MATHEMATICS_PLANE_H

#include "../Vector/Vector.h"
namespace GEM {
    class Plane {
        Vector<4, float> hypernormal_;

      public:
        Plane(const Vector<4, float> &hypernormal)
            : hypernormal_{hypernormal}
            {}

        const Vector<4, float>& hypernormal() const {
            return hypernormal_;
        }
    };
}

#endif//GAME_ENGINE_MATHEMATICS_PLANE_H
