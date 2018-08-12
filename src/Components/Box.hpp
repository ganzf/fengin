//
// Created by arroganz on 8/7/18.
//


#pragma once
# include <array>
# include <fengin-core/include/FenginCore.hpp>

// 6 faces
// 0 - top
// 1 - front left
// 2 - front right
// 3 - back right
// 4 - back left
// 5 - bottom
// Each has a texture, an alpha modifier.
namespace fengin::components {
    struct Box : public Component {
        bool wireframe{false};
        std::array<std::string, 6> textures;
        std::array<vec2i, 6> texturesCoords;
        std::array<float, 6> alpha;
    };
}


