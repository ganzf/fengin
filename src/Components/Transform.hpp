//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fengin-core/include/FenginCore.hpp"
# include "utils/position.hpp"

namespace fengin::components {
    struct Transform : futils::IComponent {
        vec2f size;
        Position position;
        float rotation;
    };
}

