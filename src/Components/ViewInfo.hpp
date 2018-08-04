//
// Created by arroganz on 1/16/18.
//


#pragma once

#include "utils/ecs.hpp"

namespace fengin::components {
    struct ViewInfo : futils::IComponent {
        // Ajouter valign, align, etc...
        float h;
        float w;
    };
}


