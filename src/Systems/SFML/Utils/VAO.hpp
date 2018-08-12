//
// Created by arroganz on 8/12/18.
//


#pragma once
# include <GL/glew.h>

namespace fengin::systems::SFMLSystems::utils {
    class VAO {
        GLuint id{0};
    public:
        VAO() = default;
        void gen() {
            glGenVertexArrays(1, &id);
            glBindVertexArray(id);
        }
    };
}

