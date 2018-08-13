//
// Created by arroganz on 8/12/18.
//


#pragma once
# include <GL/glew.h>
#include <iostream>

namespace fengin::systems::SFMLSystems::utils {
    class VAO {
        GLuint id{0};
    public:
        VAO() = default;
        void gen() {
            glGenVertexArrays(1, &id);
            auto e = glGetError();
            if (e != GL_NO_ERROR) {
                std::cerr << gluGetString(e) << std::endl;
            }
            glBindVertexArray(id);
            e = glGetError();
            if (e != GL_NO_ERROR) {
                std::cerr << gluGetString(e) << std::endl;
            }
        }
    };
}

