//
// Created by Berci on 2020. 12. 05..
//

#ifndef GAME_ENGINE_MATHEMATICS_LINE_H
#define GAME_ENGINE_MATHEMATICS_LINE_H

#include "../Vector/Vector.h"

namespace GEM {
    class Line {
        Vector<4, float> origin_;
        Vector<4, float> direction_;

      public:
        Line()
            : origin_{{0, 0, 0, 1}}
            , direction_{{0, 0, 0, 0}}
            { }

        Line(const Vector<4, float> &origin, const Vector<4, float> &direction) {
            assert(origin.at(3) == 1);
            assert(direction.at(3) == 0);

            this->origin_ = origin;
            this->direction_ = direction;
        }

        const Vector<4, float>& origin() const {
            return origin_;
        }
        const Vector<4, float>& direction() const {
            return direction_;
        }
    };
}

#endif//GAME_ENGINE_MATHEMATICS_LINE_H
