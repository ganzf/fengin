//
// Created by clara on 1/24/18.
//


#pragma once

// TODO: Add a basic System to fengin-core !
# include "Systems/SFML/System.hpp"
# include "Components/rigidBody.hpp"

namespace fengin::systems::FysicsSystems
{
    class Collision : public systems::SFMLSystems::System {
        enum State
        {
            Init = 0,
            Run
        };
        State state{Init};
        void detectCollisions() const;
    public:
        Collision() : systems::SFMLSystems::System("Collision") {}
        void run(float) override;
    };
}