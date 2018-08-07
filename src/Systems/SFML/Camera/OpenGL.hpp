//
// Created by arroganz on 8/6/18.
//


#pragma once

# include <Entities/Window.hpp>
# include <SFML/Graphics/RenderWindow.hpp>
# include <Components/Box.hpp>
# include <Components/Billboard.hpp>
# include "SFML/OpenGL.hpp"
# include "../System.hpp"

namespace fengin::systems::SFMLSystems {
    class OpenGL : public System {
        using Window = sf::RenderWindow;
        using Camera = entities::Camera;
        Window *win{nullptr};
        Camera *cam{nullptr};
//        Upon asset folder loaded, each image is loaded by name..
//    That may be heavy, but it'll work.
        std::unordered_map<std::string, GLuint> loadedGlTextures;
//        std::unordered_map<std::string, sf::Texture> loadedGlTextures;

        void init();
        void setupOpenGlVertices();


        void renderTile(vec3f pos, vec3f size, vec3f rot, const components::Box &);
        void render(float elapsed);
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