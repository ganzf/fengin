//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fengin-core/include/FenginCore.hpp"
# include "utils/rendering.hpp"
#include "ChildInfo.hpp"

namespace fengin::entities
{
    class GameObject;
}

namespace fengin::components {
    struct Children : Component {
        std::unordered_map<entities::GameObject *, entities::GameObject *> content;
        void add(entities::GameObject &obj);
        void remove(entities::GameObject &obj);
    };
}

