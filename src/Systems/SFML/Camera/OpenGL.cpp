//
// Created by arroganz on 8/6/18.
//

#include <Systems/SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/glu.h>
#include <cmath>
#include <utils/inputKeys.hpp>
#include <Components/Transform.hpp>
#include <Systems/SFML/AssetLoader.hpp>
#include <SOIL.h>
#include "OpenGL.hpp"
#include "Camera.hpp"
#include "Entities/Camera.hpp"

float _x = 0.0f;
float _y = 1000.f;
float _z = 0;

namespace fengin::systems::SFMLSystems {
    void OpenGL::init() {
        __init();
        events->send<RequestWindow>();
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
            GLint viewport[4];
            glGetIntegerv( GL_VIEWPORT, viewport );
        });
        addReaction<ResponseWindow>([this](futils::IMediatorPacket &pkg){
            auto &packet = EventManager::rebuild<ResponseWindow>(pkg);
            if (!packet.window) {
                std::cerr << "No window received" << std::endl;
                return;
            }
            win = (packet.window);
            phase++;
            glEnable(GL_TEXTURE_2D);
            sf::ContextSettings settings = win->getSettings();
            std::cout << "depth bits:" << settings.depthBits << std::endl;
            std::cout << "stencil bits:" << settings.stencilBits << std::endl;
            std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
            std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;
            this->setupOpenGlVertices();
        });
        addReaction<AssetsLoaded>([this](futils::IMediatorPacket &pkg){
            const auto &packet = EventManager::rebuild<AssetsLoaded>(pkg);
            for (auto &texture: *packet.textures) {
//
//                glActiveTexture(texIndex[_index]);
//                glBindTexture(_type, this->_id);
//                _image = SOIL_load_image(_source.c_str(), &_width, &_height, 0, SOIL_LOAD_RGB);
//                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _image);
//                SOIL_free_image_data(_image);
//                glUniform1i(glGetUniformLocation(_shaderProg, _varName.c_str()), _index);

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
//        May not be required.
//        win->setActive(true);
        glClearDepth(1.f);
        glClearColor(0.3f, 0.3f, 0.3f, 0.f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
//        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_TRUE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        glEnable(GL_BLEND);

        GLint viewport[4];
        glGetIntegerv( GL_VIEWPORT, viewport );

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        float aspect=(float)viewport[3]/(float)viewport[2];
        float screen_tiles=(float)viewport[2] / (float)64;
        float ortho_width=screen_tiles*(float)64*1.414213562373f;
        float ortho_height=ortho_width * aspect;
        glOrtho(-ortho_width / 2, ortho_width / 2, -ortho_height/2, ortho_height/2, -1250.0f, 1250.0f);
    }

    void OpenGL::renderTile(vec3f pos, vec3f size, vec3f rot, const components::Box &box) {
        auto &camPos = cam->get<components::Transform>().position;
        const auto &camC = cam->get<fengin::components::Camera>();
        auto const zoom = camC.zoom;
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, 0, -100);
//        If its a billboard or not depends what order you rotate and translate.
        glRotatef(30.0f, 1, 0, 0);
        glRotatef(-45.0f, 0, 1, 0);
        glTranslatef(-(pos.x - camPos.x) * zoom * 2, (pos.z - camPos.z) * zoom * 2, (pos.y - camPos.y) * zoom * 2);
        if (box.getEntity().has<fengin::components::Billboard>()) {
            glRotatef(-30.0f, 1, 0, 0);
            glRotatef(45.0f, 0, 1, 0);
        } else {
            glRotatef(rot.x, 0, 0, 0);
            glRotatef(rot.z, 0, 1, 0);
            glRotatef(rot.y, 0, 0, 1);
        }
//        glLoadIdentity();
////        make a 0,0,0 cube appear at the center of the screen instead of around the camera
//        glTranslatef(x, y, z);
////        This would be the size of the cube ! with a base of 10
        glScalef(zoom * size.x, zoom * size.z, zoom * size.y);
//        glEnable(GL_TEXTURE_2D);
//        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        glDepthMask(GL_FALSE);
//        glDisable(GL_DEPTH_TEST);
        glColor3f(1.0f, 1.0f, 1.0f);
        //Draw a cube
        glBindTexture(GL_TEXTURE_2D, loadedGlTextures[box.textures[0]]);
        glBegin(box.wireframe ? GL_LINES : GL_QUADS);//draw some squares
//        glBegin(GL_LINES);
//        sf::Texture::bind((const sf::Texture *) &loadedGlTextures["grass.png"]);
        // Front Face
//        glBindTexture(GL_TEXTURE_2D, loadedGlTextures["dirt1.png"]);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left
        // Back Face
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left
        glEnd();

        glBindTexture(GL_TEXTURE_2D, loadedGlTextures["grass.png"]);
        glBegin(box.wireframe ? GL_LINES : GL_QUADS);//draw some squares
        // Top Face
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right
        glEnd();
        glBindTexture(GL_TEXTURE_2D, loadedGlTextures["dirt2.png"]);
        glBegin(box.wireframe ? GL_LINES : GL_QUADS);//draw some squares
//        // Bottom Face
//        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right
//        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left
//        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left
//        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right
//        glBindTexture(GL_TEXTURE_2D, loadedGlTextures["dirt1.png"]);
        // Right face
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left
        // Left Face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left

//        // TOP RIGHT FACE
//        glColor3f(155.0f / 255.0f, 118.0f / 255.0f, 83.0f / 255.0f); // dirt
//        glVertex3f(-1.f, -1.f, -1.f);
//        glVertex3f(-1.f,  1.f, -1.f);
//        glVertex3f( 1.f,  1.f, -1.f);
//        glVertex3f( 1.f, -1.f, -1.f);
//
//        // BOTTOM LEFT FACE
//        glColor3f(155.0f / 255.0f, 118.0f / 255.0f, 83.0f / 255.0f); // dirt
//        glVertex3f( 1.f, -1.f, 1.f);
//        glVertex3f( 1.f,  1.f, 1.f);
//        glVertex3f(-1.f,  1.f, 1.f);
//        glVertex3f(-1.f, -1.f, 1.f);
//
//        // TOP LEFT FACE
//        glColor3f(124.0f / 255.0f, 94.0f / 255.0f, 66.0f / 255.0f); // dirt
//        glVertex3f(-1.f, -1.f,  1.f);
//        glVertex3f(-1.f,  1.f,  1.f);
//        glVertex3f(-1.f,  1.f, -1.f);
//        glVertex3f(-1.f, -1.f, -1.f);
//
//        // BOTTOM RIGHT FACE
//        glColor3f(124.0f / 255.0f, 94.0f / 255.0f, 66.0f / 255.0f); // dark dirt
//        glVertex3f(1.f, -1.f, -1.f);
//        glVertex3f(1.f,  1.f, -1.f);
//        glVertex3f(1.f,  1.f,  1.f);
//        glVertex3f(1.f, -1.f,  1.f);
//
//
//        // Ever so useless BOTTOM FACE
////        glColor3f(155.0f / 255.0f, 118.0f / 255.0f, 83.0f / 255.0f); // dirt
////        glVertex3f(-1.f, -1.f,  1.f);
////        glVertex3f(-1.f, -1.f, -1.f);
////        glVertex3f( 1.f, -1.f, -1.f);
////        glVertex3f( 1.f, -1.f,  1.f);
//
//        // TOP FACE
//        if (!box.wireframe) {
//            sf::Texture::bind((const sf::Texture *) &loadedGlTextures["grass.png"]);
////            glTexCoord2f(0.0f, 1.0f);
////            glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left
////            glTexCoord2f(0.0f, 0.0f);
////            glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left
////            glTexCoord2f(1.0f, 0.0f);
////            glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right
////            glTexCoord2f(1.0f, 1.0f);
////            glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right
//        } else {
//            glColor3f(0, 86.0f / 255, 0); //green
//        }
//        glTexCoord2f(0.0f, 0.0f);
//        glVertex3f(1.f, 1.f, 1.f);
//        glTexCoord2f(1.0f, 0.0f);
//        glVertex3f(1.f, 1.f, -1.f);
//        glTexCoord2f(1.0f, 1.0f);
//        glVertex3f(-1.f, 1.f, -1.f);
//        glTexCoord2f(0.0f, 1.0f);
//        glVertex3f(-1.f, 1.f, 1.f);

        glEnd();

        if (!box.getEntity().has<fengin::components::Billboard>()) {
            glBegin(GL_LINES);
            const auto hoveringHeight = 0.05f;
            const auto transparency = 0.25f;
//        glColor4f(0.9, 0.9, 0.9, transparency); // whitish grid
            // 1 - 2
            glVertex3f(1.f, 1.0f + hoveringHeight, 1.f);
            glVertex3f(1.f, 1.0f + hoveringHeight, -1.f);
            // 2 - 3
            glVertex3f(-1.f, 1.0f + hoveringHeight, -1.f);
            glVertex3f(1.f, 1.0f + hoveringHeight, -1.f);
            // 3 - 4
            glVertex3f(-1.f, 1.0f + hoveringHeight, -1.f);
            glVertex3f(-1.f, 1.0f + hoveringHeight, 1.f);
            // 4 - 1
            glVertex3f(-1.f, 1.0f + hoveringHeight, 1.f);
            glVertex3f(1.f, 1.0f + hoveringHeight, 1.f);
            glEnd();
        }
//        glEnable(GL_DEPTH_TEST);
//        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
    }

    void OpenGL::render(float elapsed) {
        static auto timer = 0.0f;
        timer += elapsed;
        if (!this->win || !this->cam) {
            auto cams = entityManager->get<components::Camera>();
            if (cams.size() > 0) {
                cam = dynamic_cast<Camera *>(&cams[0]->getEntity());
            }
            return;
        }
        // Prepare for drawing
        // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        auto go = entityManager->get<fengin::components::GameObject>();
        for (auto &obj: go) {
            if (!obj->visible)
                continue;
            auto &tr = obj->getEntity().get<components::Transform>();
//            If the gameObject has a component Billboard draw it like a billboard (1 texture)
            if (obj->getEntity().has<components::Box>())
                renderTile(tr.position, tr.size, tr.rotation, obj->getEntity().get<components::Box>());
//            else if (obj->has<components::Billboard>())
//            renderTile(tr.position.x - camPos.position.x, tr.position.z - camPos.position.z, tr.position.y - camPos.position.y,
//            tr.size.x, tr.size.z, tr.size.y);
        }
        win->display();
    }
}
