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

    void Camera::run(float) {
        const auto &cameras = entityManager->get<fengin::components::Camera>();
        for (auto &cam: cameras) {
            if (cam->target) {
                auto &camPos = cam->getEntity().get<fengin::components::Transform>();
                auto &targetPos = cam->target->get<fengin::components::Transform>();
//                camPos.position.x = targetPos.position.x;
//                camPos.position.y = targetPos.position.y;
                auto &targetTr = cam->target->get<fengin::components::Transform>();
                auto &camBody = cam->getEntity().get<fengin::components::rigidBody>();
                camBody.force.x = targetTr.position.x - camPos.position.x;
                camBody.force.y = targetTr.position.y - camPos.position.y;
                camBody.force.x = camBody.force.x > 1 ? 1 : camBody.force.x;
                camBody.force.y = camBody.force.y > 1 ? 1 : camBody.force.y;
            }
        }
    }
}