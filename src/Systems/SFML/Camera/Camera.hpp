//
// Created by arroganz on 1/3/18.
//

#pragma once

# include <SFML/Window.hpp>
# include "../System.hpp"
# include "Entities/Window.hpp"
# include "Entities/GameObject.hpp"
# include "Components/Camera.hpp"
# include "Components/World.hpp"

namespace fengin::systems::SFMLSystems
{
    struct StartingRendering {};
    class Camera : public System
    {
    public:
        Camera();
        void run(float) final;
    };

    struct RenderLayer
    {
        int layer;
        sf::Window *window;
        components::Camera *camData;
        std::vector<Entity *> objects;
    };

    struct AllLayersRendered
    {
        sf::Window *window;
        components::Camera *camData;
    };
}

//inline sf::Color &operator << (sf::Color &lhs, futils::Color const &rhs)
//{
//    //TODO: Big endian//litte endian ??
//    lhs.r = rhs.rgba[2];
//    lhs.g = rhs.rgba[1];
//    lhs.b = rhs.rgba[0];
//    lhs.a = rhs.rgba[3];
//    return lhs;
//}