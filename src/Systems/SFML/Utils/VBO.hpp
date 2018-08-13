//
// Created by arroganz on 8/12/18.
//


#pragma once

# include <GL/glew.h>
#include <vector>
#include <iostream>

namespace fengin::systems::SFMLSystems::utils {
    class VBO {
        GLuint id;
        GLuint colorId;
        std::vector<GLfloat> buffer;
        std::vector<GLfloat> colorBuffer;
    public:
        VBO() = default;

        void gen() {
            glGenBuffers(1, &id);
            auto e = glGetError();
            if (e != GL_NO_ERROR) {
                std::cerr << gluGetString(e) << std::endl;
            }
        }

        void set(std::vector<GLfloat> array) {
            buffer = array;
            bind();
            glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(buffer[0]), array.data(), GL_STATIC_DRAW);
//            auto e = glGetError();
//            if (e != GL_NO_ERROR) {
//                std::cerr << gluGetString(e) << std::endl;
//            }
        }

        void bind() {
            glBindBuffer(GL_ARRAY_BUFFER, id);
            auto e = glGetError();
            if (e != GL_NO_ERROR) {
                std::cerr << gluGetString(e) << std::endl;
            }
        }

        void bindColors() {
            glBindBuffer(GL_ARRAY_BUFFER, colorId);
            auto e = glGetError();
            if (e != GL_NO_ERROR) {
                std::cerr << gluGetString(e) << std::endl;
            }
        }

        void setColors(std::vector<GLfloat> const &colors) {
            glGenBuffers(1, &colorId);
            colorBuffer = colors;
        }

        void colorize() {
            bindColors();
            glBufferData(GL_ARRAY_BUFFER, colorBuffer.size() * sizeof(GLfloat), colorBuffer.data(), GL_STATIC_DRAW);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(
                    1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                    3,                                // size
                    GL_FLOAT,                         // type
                    GL_FALSE,                         // normalized?
                    0,                                // stride
                    (void*)0                          // array buffer offset
            );
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
            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(buffer.size() / 3)); // Starting from vertex 0; 3 vertices total -> 1 triangle
            auto e = glGetError();
            if (e != GL_NO_ERROR) {
                std::cerr << gluGetString(e) << std::endl;
            }
            glDisableVertexAttribArray(0);
            e = glGetError();
            if (e != GL_NO_ERROR) {
                std::cerr << gluGetString(e) << std::endl;
            }
            if (colorId > 0) {
                colorize();
            }
        }
    };
}

