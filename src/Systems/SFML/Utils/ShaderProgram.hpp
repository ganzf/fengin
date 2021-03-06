//
// Created by arroganz on 8/12/18.
//


#pragma once

#include <vector>
#include <ostream>
#include <iostream>
#include <experimental/filesystem>
#include "Shader.hpp"

namespace fengin::systems::SFMLSystems::utils {
    class ShaderProgram {
        GLuint id{0};
        GLint linkResult{0};
        std::vector<Shader *> loadedShaders;
    public:
        ShaderProgram() = default;
        bool loadShadersFromDir(std::string const &directory, Shader::ShaderType type) {
            std::cout << "Loading all shaders in " << directory << std::endl;
            const auto fsPath = std::experimental::filesystem::path(directory);
            for (auto & p : std::experimental::filesystem::directory_iterator(fsPath)) {
                if (!std::experimental::filesystem::is_directory(p.path())) {
                    auto *shader = new Shader(p.path(), type);
                    loadedShaders.push_back(shader);
                    if (type == Shader::ShaderType::Vertex) {
                        std::cout << "Loaded Vertex shader " << p.path() << std::endl;
                    } else if (type == Shader::ShaderType::Fragment) {
                        std::cout << "Loaded Fragment shader " << p.path() << std::endl;
                    }
                }
            }
        }

        bool compile() {
            std::cout << "Linking program" << std::endl;
            id = glCreateProgram();
            // Attach each shader
            for (auto &shader: loadedShaders) {
                glAttachShader(id, shader->getId());
            }
            // Link program
            glLinkProgram(id);
            int InfoLogLength;
            // Check the program
            glGetProgramiv(id, GL_LINK_STATUS, &linkResult);
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
            if ( InfoLogLength > 0 ){
                std::vector<char> ProgramErrorMessage(InfoLogLength+1);
                glGetProgramInfoLog(id, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
                std::cerr << &ProgramErrorMessage[0] << std::endl;
                return false;
            }
            // Detaching all shaders
            for (auto &shader: loadedShaders) {
                glDetachShader(id, shader->getId());
            }
            // Deleting all shaders
            for (auto &shader: loadedShaders) {
                shader->free();
            }
            return linkResult == GL_TRUE;
        }

        void use() {
            std::cout << "Using program " << id << std::endl;
            glUseProgram(id);
            auto e = glGetError();
            if (e != GL_NO_ERROR) {
                std::cerr << gluGetString(e) << std::endl;
            }
        }

        GLuint getId() const {
            return id;
        }
    };
}

