//
// Created by arroganz on 8/12/18.
//


#pragma once
# include <GL/glew.h>

namespace fengin::systems::SFMLSystems::utils {
    class VAO {
        GLuint id;
    public:
        explicit VAO() {
            glGenVertexArrays(1, &id);
            glBindVertexArray(id);
        }
    };
}

