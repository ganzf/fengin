//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fengin-core/include/FenginCore.hpp"

namespace fengin::entities
{
    class GameObject;
    class Window;
}

namespace fengin::components {
    struct Camera : Component {
        enum FollowMode
        {
            Instant,
            Slow,
            DistanceFirst
        };

        int viewDistance{10};
        float zoom{45};
        bool debugMode{false};
        bool activated;
        FollowMode mode;
        std::string name;
        entities::Window *window;
        entities::GameObject *target;
    };
}

