//
// Created by arroganz on 2018-07-31
//

#include "Fysix.hpp"
#include "Collision.hpp"
#include "RigidBody.hpp"

extern "C" fengin::System *build()
{
    return new fengin::Fysix();
}

namespace fengin {
    Fysix::Fysix() {
        name = "Fysix";
    }

    void Fysix::init() {
        addReaction<fengin::events::Shutdown>([this](futils::IMediatorPacket &) {
            entityManager->removeSystem(name);
        });
        entityManager->addSystem<fengin::systems::FysicsSystems::RigidBody>();
        entityManager->addSystem<fengin::systems::FysicsSystems::Collision>();
        state = Run;
    }

    void Fysix::run(float) {
        switch (state) {
            case Init :
                return init();
            case Run :
                return;
        }
    }
}