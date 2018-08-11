//
// Created by arroganz on 1/13/18.
//

#include <Components/Hoverable.hpp>
#include <Components/AbsoluteTransform.hpp>
#include "utils/inputKeys.hpp"
#include "Hoverable.hpp"

namespace fengin::systems::SFMLSystems
{
    void Hoverable::update(futils::MouseMoved const &mouse)
    {
        auto objects = entityManager->get<components::Hoverable>();
        for (auto obj: objects)
        {
            auto absolute = obj->getEntity().get<components::AbsoluteTransform>();
            if (mouse.current.x >= absolute.position.x && mouse.current.x <= absolute.position.x + absolute.size.w
                && mouse.current.y >= absolute.position.y && mouse.current.y <= absolute.position.y + absolute.size.h) {
                if (!obj->hovered) {
                    obj->onEnter();
                }
                obj->onHover();
                obj->hovered = true;
            } else {
                if (obj->hovered)
                    obj->onLeave();
                obj->hovered = false;
            }
        }
    }

    void Hoverable::init() {
        __init();
        addReaction<futils::MouseMoved>([this](futils::IMediatorPacket &pkg) {
            auto &packet = EventManager::rebuild<futils::MouseMoved>(pkg);
            update(packet);
        });
        phase = Run;
    }

    void Hoverable::run(float) {
        switch (phase)
        {
            case Init: return init();
            case Run: return ;
        }
    }
}