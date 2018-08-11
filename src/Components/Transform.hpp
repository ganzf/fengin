//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fengin-core/include/FenginCore.hpp"
# include "utils/position.hpp"

namespace fengin::components {
    struct Transform : Component {
        vec3f size;
        vec3f position;
        vec3f rotation;
    };
}

