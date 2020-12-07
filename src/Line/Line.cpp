//
// Created by Berci on 2020. 12. 06..
//

#include "./Line.h"

namespace GEM {
    Line::Line(const Vector<4, float> &origin, const Vector<4, float> &direction) {
        assert(origin.at(3) == 1);
        assert(direction.at(3) == 0);

        this->origin_ = origin;
        this->direction_ = direction;
    }

    const Vector<4, float> &Line::origin() const {
        return origin_;
    }

    const Vector<4, float> &Line::direction() const {
        return direction_;
    }

    Vector<4, float> point_along_line(const Line& line, const float t) {
        return line.origin() + line.direction() * t;
    }
}
