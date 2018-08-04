//
// Created by arroganz on 1/13/18.
//


#pragma once

# include "Systems/SFML/System.hpp"
# include "Components/rigidBody.hpp"

namespace fengin::systems::FysicsSystems
{
    class RigidBody : public systems::SFMLSystems::System {
        enum State
        {
            Init = 0,
            Run
        };
        State state{Init};
        void update(float);
        void init();
    public:
        RigidBody() : systems::SFMLSystems::System("RigidBody") {}
        void run(float) override;
    };
}

