//
// Created by clara on 1/24/18.
//

#include <Components/AbsoluteTransform.hpp>
#include <Components/Border.hpp>
#include <Components/Image.hpp>
#include "Collision.hpp"

namespace fengin::systems::FysicsSystems {

    void Collision::detectCollisions() const {
        auto rigidBody = entityManager->get<components::Image>();

        unsigned int i = 0;

        if (rigidBody.size() <= 1) {
            return;
        }

        while (i < rigidBody.size() - 1) {
            unsigned int j = i + 1;

            while (j < rigidBody.size()) {

                auto first = rigidBody[i]->getEntity().get<components::AbsoluteTransform>();
                auto second = rigidBody[j]->getEntity().get<components::AbsoluteTransform>();

                if (first.position.x < second.position.x + second.size.w
                    && first.position.x + first.size.w > second.position.x
                    && first.position.y < second.position.y + second.size.h
                    && first.size.h + first.position.y > second.position.y) {


                    fengin::events::Collision pkg;

                    pkg.first = &rigidBody[i]->getEntity();
                    pkg.second = &rigidBody[j]->getEntity();

                    events->send<fengin::events::Collision>(pkg);
                    return ;
/*
                    if (rigidBody[i]->getEntity().has<components::Border>()) {
                        rigidBody[i]->getEntity().get<components::Border>().color = futils::Blueviolet;
                        rigidBody[i]->getEntity().get<components::Border>().thickness = 4;
                        rigidBody[i]->getEntity().get<components::Border>().visible = true;
                    }
                    if (rigidBody[j]->getEntity().has<components::Border>()) {
                        rigidBody[j]->getEntity().get<components::Border>().color = futils::Blueviolet;
                        rigidBody[j]->getEntity().get<components::Border>().thickness = 4;
                        rigidBody[j]->getEntity().get<components::Border>().visible = true;
                    }*/
                }

                j++;
            }
            i++;
        }
    }

    void Collision::run(float) {
        switch (state) {
            case State::Init:
                state = State::Run;
                __init();
                return;
            case State::Run: return detectCollisions();
        }
        //static float time = 0.0;
        //time += elapsed;
    }
}