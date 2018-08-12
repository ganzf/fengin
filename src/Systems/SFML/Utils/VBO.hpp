//
// Created by arroganz on 8/12/18.
//


#pragma once

# include <GL/glew.h>
#include <vector>

namespace fengin::systems::SFMLSystems::utils {
    class VBO {
        GLuint id;
    public:
        VBO() {
            glGenBuffers(1, &id);
        }

        void set(std::vector<GLfloat> array) {
            bind();
            glBufferData(GL_ARRAY_BUFFER, sizeof(array.data()), array.data(), GL_STATIC_DRAW);
        }

        void bind() {
            glBindBuffer(GL_ARRAY_BUFFER, id);

        }

        void draw() {
            // 1st attribute buffer : vertices
            glEnableVertexAttribArray(0);
            bind();
            glVertexAttribPointer(
                    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
            );
            // Draw the triangle !
            glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
            glDisableVertexAttribArray(0);
        }
    };
}

