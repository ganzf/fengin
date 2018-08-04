//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fengin-core/include/FenginCore.hpp"

namespace fengin::components {
    struct GameObject : futils::IComponent {
        bool visible{true};
        void show() {
            visible = true;
        }
        void hide() {
            visible = false;
        }
    };
}