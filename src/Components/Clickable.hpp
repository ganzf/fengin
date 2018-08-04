//
// Created by clara on 1/11/18.
//


#pragma once

# include "fengin-core/include/FenginCore.hpp"

namespace fengin::components {
    struct Clickable : futils::IComponent {
        bool waitForRelease{false};
        std::function<void()> func;
    };
}