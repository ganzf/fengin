//
// Created by arroganz on 2018-07-29
//

#include "SFML.hpp"
#include "Window.hpp"
#include "Input.hpp"
#include "Camera/Camera.hpp"
#include "Grid.hpp"
#include "Children.hpp"
#include "Border.hpp"
#include "Image.hpp"
#include "Clickable.hpp"
#include "Text.hpp"
#include "AssetLoader.hpp"
#include "ListView.hpp"
#include "Hoverable.hpp"
#include "Editable.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"

extern "C" futils::ISystem *build()
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
    entityManager->addSystem<SFMLSystems::Input>();
    entityManager->addSystem<SFMLSystems::GameObject>();
    entityManager->addSystem<SFMLSystems::Camera>();
    entityManager->addSystem<SFMLSystems::Children>();
    entityManager->addSystem<SFMLSystems::Grid>();
    entityManager->addSystem<SFMLSystems::AssetLoader>();
    entityManager->addSystem<SFMLSystems::ListView>();
    entityManager->addSystem<SFMLSystems::Border>();
    entityManager->addSystem<SFMLSystems::Text>();
    entityManager->addSystem<SFMLSystems::Image>();
    entityManager->addSystem<SFMLSystems::Clickable>();
    entityManager->addSystem<SFMLSystems::Hoverable>();
    entityManager->addSystem<SFMLSystems::Editable>();
    entityManager->addSystem<SFMLSystems::Sprite>();
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