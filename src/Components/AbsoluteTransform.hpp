//
// Created by arroganz on 1/5/18.
//


#pragma once

# include "fengin-core/include/FenginCore.hpp"

namespace fengin::components {
    struct AbsoluteTransform : Component {
        vec2i position;
        vec2i size;
    };
}


