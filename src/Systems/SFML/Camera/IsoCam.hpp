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

        std::unordered_map<std::string, fengin::components::Camera *> knownCameras;
        std::unordered_map<futils::IEntity *, sf::RenderWindow *> camToWindow;
        std::unordered_multimap<int, futils::IEntity *> layout;

        void renderWindow(futils::IEntity &cam);
        void drawCamCrosshair(components::Camera &, sf::RenderWindow *);
        void sortGameObjects();
        void renderCam(futils::IEntity &, components::Camera &, components::World &);
        void renderEachCam();
        void init();
    public:
        IsoCam() : System("IsoCam") {}
        virtual void run(float) override;
    };
}