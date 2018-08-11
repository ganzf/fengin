//
// Created by arroganz on 12/16/17.
//

#include <Components/Transform.hpp>
#include "fengin-core/include/events.hpp"
#include "Log.hpp"

extern "C" fengin::System *build()
{
    return new fengin::Log();
}

namespace fengin {
    Log::Log() {
        name = "Log";
    }

    void Log::init() {
        phase++;
        events->require<std::string>(this, [this](futils::IMediatorPacket &pkg) {
            auto &s = EventManager::rebuild<std::string>(pkg);
            std::cout << " Log --> \t" << s << std::endl;
        });
        addReaction<fengin::components::Transform>([this](futils::IMediatorPacket &pkg) {
            auto &t = EventManager::rebuild<fengin::components::Transform>(pkg);
            std::cout << " Log --> Transform \t pos(" <<
                      t.position.x << ", " <<
                      t.position.y << ", " <<
                      t.position.z << ") siz(" <<
                      t.size.x << ", " <<
                      t.size.y << ", " <<
                      t.size.z << ")" << std::endl;
        });
        addReaction<fengin::events::Shutdown>([this](futils::IMediatorPacket &) {
            entityManager->removeSystem(name);
        });
    }

    void Log::run(float) {
        switch (phase) {
            case 0:
                return init();
        }
    }
}