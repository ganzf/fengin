//
// Created by arroganz on 1/13/18.
//

#pragma once

# include "fengin-core/include/FenginCore.hpp"

namespace fengin::components {
    struct Hoverable : futils::IComponent {
        using Action = std::function<void()>;

        Action onHover{[](){}};
        Action onEnter{[](){}};
        Action onLeave{[](){}};

        bool hovered{false};
    };
}