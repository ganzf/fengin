//
// Created by clara on 1/3/18.
//

#pragma once

# include "fengin-core/include/FenginCore.hpp"

namespace fengin::components {
    struct Image : futils::IComponent {
        std::string file;
        vec2i position{0, 0};
        vec2i size{-1, -1};
    };
}