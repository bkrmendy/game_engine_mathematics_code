//
// Created by Berci on 2020. 12. 06..
//

#ifndef GAME_ENGINE_MATHEMATICS_RC_CUSTOM_GENERATORS_H
#define GAME_ENGINE_MATHEMATICS_RC_CUSTOM_GENERATORS_H

#include "rapidcheck.h"

#include "../src/Vector/Vector.h"

namespace rc {
    template<>
    struct Arbitrary<GEM::Vector<4, float>> {
        static Gen<GEM::Vector<4, float>> arbitrary() {
            return gen::construct<GEM::Vector<4, float>>()
        }
    };
}

#endif//GAME_ENGINE_MATHEMATICS_RC_CUSTOM_GENERATORS_H
