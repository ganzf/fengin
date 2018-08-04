//
// Created by arroganz on 8/4/18.
//


#pragma once

#include <utils/ecs.hpp>
#include <Components/Transform.hpp>

namespace fengin::entities {
    class Block: public futils::IEntity {
    public:
        Block(futils::Vec3d<float> position) {
            auto &tr = attach<fengin::components::Transform>();
            tr.size.x = 1;
            tr.size.y = 1;
            tr.size.z = 1;
            tr.position.x = -0.5f;
            tr.position.y = -0.5f;
            tr.position.z = 0;
        }
    };
}

