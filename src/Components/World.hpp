//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fengin-core/include/FenginCore.hpp"

namespace fengin::components {
    struct World : Component {
        enum class Type {
            Normal = 0,
            Isometric
        };
        World(Type type = Type::Normal): type(type) {}

        int unit{2};
        vec3f size;
        std::string name;
        Type type;
    };
}



