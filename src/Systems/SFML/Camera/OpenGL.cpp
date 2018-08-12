//
// Created by arroganz on 8/6/18.
//

#include <Systems/SFML/Window.hpp>
#include <utils/inputKeys.hpp>
#include <Components/Transform.hpp>
#include <Systems/SFML/AssetLoader.hpp>
#include <SOIL.h>
#include "OpenGL.hpp"
#include "Camera.hpp"
#include "Entities/Camera.hpp"

float _x = 0.0f;
float _y = 0.0f;
float _z = 0.0f;

namespace fengin::systems::SFMLSystems {
    void OpenGL::init() {
        __init();
        addReaction<futils::Keys>([&_x, &_y, &_z](futils::IMediatorPacket &pkg){
            auto &key = EventManager::rebuild<futils::Keys>(pkg);
            if (key == futils::Keys::X) {
                _x -= 1;
            }
            if (key == futils::Keys::C) {
                _x += 1;
            }
            if (key == futils::Keys::Y) {
                _y -= 1;
            }
            if (key == futils::Keys::U) {
                _y += 1;
            }
            if (key == futils::Keys::Z) {
                _z -= 1;
            }
            if (key == futils::Keys::A) {
                _z += 1;
            }
        });
        addReaction<ResponseWindow>([this](futils::IMediatorPacket &pkg){
            auto &packet = EventManager::rebuild<ResponseWindow>(pkg);
            if (!packet.window) {
                std::cerr << "No window received" << std::endl;
                return;
            }
            win = (packet.window);
            glewExperimental = GL_TRUE;
            if (glewInit() != GLEW_OK) {
                events->send<events::Shutdown>();
                std::cerr << "GlewInit Failed." << std::endl;
            } else {
                std::cout << "GlewInit ok" << std::endl;
            }
            phase++;
            sf::ContextSettings settings = win->getSettings();
            std::cout << "depth bits:\t" << settings.depthBits << std::endl;
            std::cout << "stencil bits:\t" << settings.stencilBits << std::endl;
            std::cout << "antialiasing level:\t" << settings.antialiasingLevel << std::endl;
            std::cout << "version:\t" << settings.majorVersion << "." << settings.minorVersion << std::endl;
            std::cout << "GL VERSION:\t" << glGetString(GL_VERSION) << std::endl;
            std::cout << "GLSL VERSION:\t" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
            std::cout << "GL EXTENSIONS:\t" << glGetString(GL_EXTENSIONS) << std::endl;
            this->setupOpenGlVertices();
        });
        addReaction<AssetsLoaded>([this](futils::IMediatorPacket &pkg){
            const auto &packet = EventManager::rebuild<AssetsLoaded>(pkg);
            for (auto &texture: *packet.textures) {
                GLuint textureId = SOIL_load_OGL_texture(
                        std::string("./resources/" + texture.first).c_str(),
                                SOIL_LOAD_AUTO,
                                SOIL_CREATE_NEW_ID,
                                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                        );

                /* check for an error during the load process */
                if( 0 == textureId )
                {
                    std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
                } else {
                    events->send<std::string>("Texture " + texture.first + " loaded into OpenGL with soil and id " + std::to_string(textureId));
                    this->loadedGlTextures[texture.first] = textureId;
//                    Allocate 1 name for texture textureId
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                }
                std::cout << "Received texture " << texture.first << " in openGL " << std::endl;
            }
        });
        events->send<RequestWindow>();
        events->send<RequestAssets>();
    }

    void OpenGL::setupOpenGlVertices() {
        win->setVerticalSyncEnabled(true);
        vao.gen();
        vbo.gen();
        std::vector<GLfloat> triangle;
//        -1.0f, -1.0f, 0.0f,
//         1.0f, -1.0f, 0.0f,
//         0.0f,  1.0f, 0.0f,
        triangle.push_back(-1.0f);
        triangle.push_back(-1.0f);
        triangle.push_back(0.0f);

        triangle.push_back(1.0f);
        triangle.push_back(-1.0f);
        triangle.push_back(0.0f);

        triangle.push_back(0.0f);
        triangle.push_back(1.0f);
        triangle.push_back(0.0f);

        vbo.set(triangle);
        shaderProgram.loadShadersFromDir("./Shaders/vertexShaders/", utils::Shader::ShaderType::Vertex);
        shaderProgram.loadShadersFromDir("./Shaders/fragmentShaders/", utils::Shader::ShaderType::Fragment);
        if (shaderProgram.compile()) {
            events->send<std::string>("Compiled shaders successfully");
        }
        shaderProgram.use();
    }

    void OpenGL::renderTile(vec3f pos, vec3f size, vec3f rot, const components::Box &box) {
        auto &camPos = cam->get<components::Transform>().position;
        const auto &camC = cam->get<fengin::components::Camera>();
        auto const zoom = camC.zoom;
    }

    void OpenGL::render(float elapsed) {
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        vbo.draw();
//        static auto timer = 0.0f;
//        timer += elapsed;
//        if (!this->win || !this->cam) {
//            auto cams = entityManager->get<components::Camera>();
//            if (cams.size() > 0) {
//                cam = dynamic_cast<Camera *>(&cams[0]->getEntity());
//            }
//            return;
//        }
//        auto go = entityManager->get<fengin::components::GameObject>();
//        for (auto &obj: go) {
//            if (!obj->visible)
//                continue;
//            auto &tr = obj->getEntity().get<components::Transform>();
//            if (obj->getEntity().has<components::Box>())
//                renderTile(tr.position, tr.size, tr.rotation, obj->getEntity().get<components::Box>());
//        }
        win->display();
    }
}
