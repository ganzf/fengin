//
// Created by arroganz on 1/2/18.
//

#pragma once

# include "fengin-core/include/FenginCore.hpp"
# include "Components/Input.hpp"

namespace fengin::entities
{
    class Input : public futils::IEntity
    {
    public:
        Input() {
            attach<fengin::components::Input>();
        }
        ~Input()
        {
            detach<fengin::components::Input>();
        }

        void setActivated(bool activated) {
            auto &input = get<components::Input>();
            input.activated = activated;
        }

        void on(futils::Keys key, std::function<void()> reaction) {
            auto &input = get<components::Input>();
            input.map[key] = reaction;
        }
    };
}
