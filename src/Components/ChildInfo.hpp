//
// Created by arroganz on 1/8/18.
//


#pragma once

# include "fengin-core/include/FenginCore.hpp"
# include "utils/rendering.hpp"

namespace fengin::entities
{
    class GameObject;
}

namespace fengin::components {
    struct ChildInfo : futils::IComponent {
        vec3f offset;
        vec3f relSize;
        bool isGridRelative{false};
        futils::IEntity *parent{nullptr};
    };
}

