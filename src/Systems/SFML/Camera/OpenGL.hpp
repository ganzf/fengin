//
// Created by arroganz on 8/6/18.
//


#pragma once

#include <Entities/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
# include "SFML/OpenGL.hpp"
# include "../System.hpp"

namespace fengin::systems::SFMLSystems {
    class OpenGL : public System {
        using Window = sf::RenderWindow;
        using Camera = entities::Camera;
        Window *win{nullptr};
        Camera *cam{nullptr};

        void init();
        void setupOpenGlVertices();


        void renderTile(float x, float y, float z, float ry);
        void render(float);
    public:
        OpenGL(): System("OpenGL") {}
        virtual void run(float elapsed) final {
            if (phase == 0) {
                return init();
            } else {
                return render(elapsed);
            }
        }
    };
}