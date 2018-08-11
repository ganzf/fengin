//
// Created by arroganz on 8/7/18.
//


#pragma once
# include <fengin-core/include/FenginCore.hpp>

namespace fengin::components {
    struct Billboard : public futils::IComponent {
        bool isVertical;
        float alpha;
        vec2i texCoords;
        std::string sprite;
    };
}


