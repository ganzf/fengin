//
// Created by arroganz on 1/3/18.
//

#include <SFML/Graphics.hpp>
#include <Entities/Camera.hpp>
#include "utils/inputKeys.hpp"
#include "Camera.hpp"
#include "../Window.hpp"
#include "NormalCam.hpp"
#include "IsoCam.hpp"

using WorldAttached = futils::ComponentAttached<fengin::components::World>;
using WorldDetached = futils::ComponentDeleted<fengin::components::World>;

namespace fengin::systems::SFMLSystems
{
    Camera::Camera(): System("Camera") {
        afterBuild = [this](){
            __init();
            addReaction<WorldAttached>([this](futils::IMediatorPacket &pkg){
                auto &world = futils::Mediator::rebuild<WorldAttached>(pkg);
                if (world.compo.type == fengin::components::World::Type::Normal) {
                    entityManager->addSystem<fengin::systems::SFMLSystems::NormalCam>();
                } else if (world.compo.type == fengin::components::World::Type::Isometric) {
                    entityManager->addSystem<fengin::systems::SFMLSystems::IsoCam>();
                }
            });
            addReaction<WorldDetached>([this](futils::IMediatorPacket &pkg){
                auto &world = futils::Mediator::rebuild<WorldDetached >(pkg);
                if (world.compo.type == fengin::components::World::Type::Normal) {
                    entityManager->removeSystem("NormalCam");
                } else if (world.compo.type == fengin::components::World::Type::Isometric) {
                    entityManager->removeSystem("IsoCam");
                }
            });
        };
    }
}