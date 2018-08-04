//
// Created by arroganz on 1/13/18.
//


#pragma once

# include "fengin-core/include/FenginCore.hpp"

namespace fengin::components {
    struct rigidBody : futils::IComponent {
        float weight;
        vec3f force;
    };
}


