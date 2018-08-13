//
// Created by arroganz on 2018-07-29
//

#include "SFML.hpp"
#include "Window.hpp"
#include "Input.hpp"
#include "Camera/Camera.hpp"

extern "C" fengin::System *build()
{
    return new fengin::systems::SFMLRenderer();
}

fengin::systems::SFMLRenderer::SFMLRenderer()
{
    name = "SFML";
}

void fengin::systems::SFMLRenderer::init() {
    state = NONE;
    entityManager->addSystem<SFMLSystems::Window>();
    entityManager->addSystem<SFMLSystems::Camera>();
    entityManager->addSystem<SFMLSystems::Input>();
    addReaction<events::Shutdown>([this](futils::IMediatorPacket &){
        entityManager->removeSystem(name);
    });
}

void fengin::systems::SFMLRenderer::run(float)
{
    switch (state) {
        case NONE: return ;
        case INIT : return init();
        case RENDER : return ;
    }
}