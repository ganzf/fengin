//
// Created by arroganz on 1/1/18.
//

#pragma once

# include "fengin-core/include/FenginCore.hpp"

namespace fengin::systems::SFMLSystems
{
    class System : public fengin::System
    {
    protected:
        int phase{0};
        void shutdown()
        {
            entityManager->removeSystem(name);
        }
        void __init()
        {
            addReaction<events::Shutdown>([this](futils::IMediatorPacket &){
                shutdown();
            });
        }

        System(std::string const &systemName)
        {
            name = "SFML/" + systemName;
        }
    public:
        virtual ~System() {}
    };
}
