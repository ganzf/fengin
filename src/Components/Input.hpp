//
// Created by arroganz on 1/2/18.
//

#pragma once

# include "fengin-core/include/FenginCore.hpp"
# include "utils/inputKeys.hpp"

namespace fengin::components {
    struct Input : Component {
        bool activated{false};
        std::string name;
        std::unordered_map<futils::InputSequence, std::function<void()>> map;
    };
}
