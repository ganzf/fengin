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
            attach<fengin::components::Transform>();
        }
    };
}

