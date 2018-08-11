//
// Created by arroganz on 8/4/18.
//


#pragma once

#include <fengin-core/include/ecs.hpp>
#include <Components/Transform.hpp>

namespace fengin::entities {
    class Block: public Entity {
    public:
        explicit Block() {
            auto &tr = attach<fengin::components::Transform>();
            tr.size.x = 1;
            tr.size.y = 1;
            tr.size.z = 1;
            tr.position.x = 0;
            tr.position.y = 0;
            tr.position.z = 0;
        }
    };
}

