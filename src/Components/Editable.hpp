//
// Created by arroganz on 1/13/18.
//


#pragma once

# include "fengin-core/include/FenginCore.hpp"

namespace fengin::components {
    struct Editable : futils::IComponent {
        bool hasFocus{false};
        std::function<void()> onFocus{[](){}};
        std::function<void()> onFocusLost{[](){}};
        int index{0};
    };
}

