//
// Created by arroganz on 1/5/18.
//


#pragma once

# include "fengin-core/include/FenginCore.hpp"
# include "utils/rendering.hpp"

namespace fengin::components
{
    struct Border : futils::IComponent
    {
        bool right{true};
        bool left{true};
        bool up{true};
        bool down{true};
        bool visible;
        futils::Color color;
        int thickness{1};
    };
}

