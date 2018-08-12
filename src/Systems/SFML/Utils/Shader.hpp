//
// Created by arroganz on 8/12/18.
//


#pragma once
# include <string>
# include <GL/glew.h>

namespace fengin::systems::SFMLSystems::utils {
    class Shader {
    public:
        enum ShaderType {
            Vertex = 0,
            Fragment
        };

    private:
        std::string path{""};
        ShaderType type;
        GLuint id{0};
        bool deleted{false};

    public:
        Shader() = default;
        Shader(std::string const &pathToSource, ShaderType type): path(pathToSource), type(type) {
            loadFromFile(pathToSource, type);
        }
        bool loadFromFile(std::string const &path, ShaderType type);
        void free() {
            glDeleteShader(id);
            deleted = true;
        }
        bool isDeleted() const {
            return deleted;
        }
        GLuint getId() const {
            return id;
        }
    };
}


