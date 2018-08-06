//
// Created by arroganz on 8/6/18.
//

#include <Systems/SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/glu.h>
#include <cmath>
#include <utils/inputKeys.hpp>
#include <Components/Transform.hpp>
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
            auto &key = futils::Mediator::rebuild<futils::Keys>(pkg);
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
            auto &packet = futils::Mediator::rebuild<ResponseWindow>(pkg);
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
        events->send<RequestWindow>();

    }

    void OpenGL::setupOpenGlVertices() {
        win->setVerticalSyncEnabled(true);
//        May not be required.
//        win->setActive(true);
        glClearDepth(1.f);
        glClearColor(0.3f, 0.3f, 0.3f, 0.f);
        glEnable(GL_DEPTH_TEST);
//        glDepthFunc(GL_LESS);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_TRUE);

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

    void OpenGL::renderTile(float x, float y, float z, float ry = -45) {
        auto const zoom = 45.0f;
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0,0,-100);
        glRotatef(30, 1, 0, 0);
        glRotatef(ry, 0, 1, 0);
        glTranslatef(-x * zoom * 2, y * zoom * 2, z * zoom * 2);
//        glLoadIdentity();
////        make a 0,0,0 cube appear at the center of the screen instead of around the camera
//        glTranslatef(x, y, z);
////        This would be the size of the cube ! with a base of 10
        glScalef(zoom, zoom, zoom);
//        glRotatef(60, 1.f, 0.f, 0.f);
//        glRotatef(ry, 0.f, 1.f, 0.f);

//        glRotatef(60,1,0,0);

//        glRotatef(angle * 90, 0.f, 0.f, 1.f);



        //Draw a cube
        glBegin(GL_QUADS);//draw some squares
        glColor3f(155.0f / 255.0f,118.0f / 255.0f ,83.0f / 255.0f); // dirt
        glVertex3f(-1.f, -1.f, -1.f);
        glVertex3f(-1.f,  1.f, -1.f);
        glVertex3f( 1.f,  1.f, -1.f);
        glVertex3f( 1.f, -1.f, -1.f);

        glColor3f(124.0f / 255.0f,94.0f / 255.0f ,66.0f / 255.0f); // dirt
        glVertex3f( 1.f, -1.f, 1.f);
        glVertex3f( 1.f,  1.f, 1.f);
        glVertex3f(-1.f,  1.f, 1.f);
        glVertex3f(-1.f, -1.f, 1.f);

        glColor3f(124.0f / 255.0f,94.0f / 255.0f ,66.0f / 255.0f); // dirt
        glVertex3f(-1.f, -1.f,  1.f);
        glVertex3f(-1.f,  1.f,  1.f);
        glVertex3f(-1.f,  1.f, -1.f);
        glVertex3f(-1.f, -1.f, -1.f);

        glColor3f(124.0f / 255.0f,94.0f / 255.0f ,66.0f / 255.0f); // dirt
        glVertex3f(1.f, -1.f, -1.f);
        glVertex3f(1.f,  1.f, -1.f);
        glVertex3f(1.f,  1.f,  1.f);
        glVertex3f(1.f, -1.f,  1.f);

        glColor3f(124.0f / 255.0f,94.0f / 255.0f ,66.0f / 255.0f); // dirt
        glVertex3f(-1.f, -1.f,  1.f);
        glVertex3f(-1.f, -1.f, -1.f);
        glVertex3f( 1.f, -1.f, -1.f);
        glVertex3f( 1.f, -1.f,  1.f);

        glColor3f(0, 86.0f / 255, 0); //green
        glVertex3f( 1.f, 1.f,  1.f);
        glVertex3f( 1.f, 1.f, -1.f);
        glVertex3f(-1.f, 1.f, -1.f);
        glVertex3f(-1.f, 1.f,  1.f);

        glEnd();

        glBegin(GL_LINES);
        glColor3f(0.9, 0.9, 0.9); // whitish grid
        // 1 - 2
        glVertex3f( 1.f, 1.02f,  1.f);
        glVertex3f( 1.f, 1.02f, -1.f);
        // 2 - 3
        glVertex3f(-1.f, 1.02f, -1.f);
        glVertex3f( 1.f, 1.02f, -1.f);
        // 3 - 4
        glVertex3f(-1.f, 1.02f, -1.f);
        glVertex3f(-1.f, 1.02f,  1.f);
        // 4 - 1
        glVertex3f(-1.f, 1.02f,  1.f);
        glVertex3f( 1.f, 1.02f,  1.f);
        glEnd();
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
        auto &camPos = cam->get<components::Transform>();
        for (auto &obj: go) {
            if (!obj->visible)
                continue;
            auto &tr = obj->getEntity().get<components::Transform>();
            renderTile(tr.position.x - camPos.position.x, tr.position.z - camPos.position.z, tr.position.y - camPos.position.y);
        }
        win->display();
    }
}
