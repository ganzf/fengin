//
// Created by arroganz on 8/12/18.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Shader.hpp"

namespace fengin::systems::SFMLSystems::utils {
    static const std::unordered_map<Shader::ShaderType, GLenum> fromShaderTypeToGlType= {
            { Shader::ShaderType::Vertex, GL_VERTEX_SHADER},
            { Shader::ShaderType::Fragment, GL_FRAGMENT_SHADER},
    };

    bool Shader::loadFromFile(std::string const &path, ShaderType type) {
        // Create the shaders
        id = glCreateShader(fromShaderTypeToGlType.at(type));

        // Read the Shader code from the file
        std::string ShaderCode;
        std::ifstream ShaderStream(path, std::ios::in);
        if (ShaderStream.is_open()) {
            std::stringstream sstr;
            sstr << ShaderStream.rdbuf();
            ShaderCode = sstr.str();
            ShaderStream.close();
        } else {
            std::cerr << "Impossible to open " << path << ". Are you in the right directory ? Don't forget to read the FAQ !" << std::endl;
            id = 0;
            return false;
        }

        GLint Result = GL_FALSE;
        int InfoLogLength;

        // Compile Shader
        std::cout << "Compiling shader : " << path << std::endl;
        char const * sourcePointer = ShaderCode.c_str();
        glShaderSource(id, 1, &sourcePointer , nullptr);
        glCompileShader(id);

        // Check Shader
        glGetShaderiv(id, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> shaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(id, InfoLogLength, nullptr, &shaderErrorMessage[0]);
            std::cout << &shaderErrorMessage[0] << std::endl;
        }
        return true;
    }
}