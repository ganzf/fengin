//
// Created by arroganz on 8/3/18.
//

#pragma once
# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include "../System.hpp"
# include "Entities/Window.hpp"
# include "Entities/GameObject.hpp"
# include "Components/Camera.hpp"
# include "Components/World.hpp"

namespace fengin::systems::SFMLSystems {
    class IsoCam : public System {
        enum States {
            Init = 0,
            Run
        };
        int state{Init};

    public:
        IsoCam() : System("IsoCam") {}
        virtual void run(float) override {
            switch (state) {
                case States::Init:
                    state += 1;
                    return __init();
            }
        };
    };
}