//
// Created by arroganz on 1/1/18.
//

#ifndef FENGIN_WINDOW_HPP
#define FENGIN_WINDOW_HPP

# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include "System.hpp"
# include "Entities/Window.hpp"
# include "Components/Color.hpp"

namespace fengin::systems::SFMLSystems
{
    struct RequestWindow
    {
        Entity *camera;
    };

    struct ResponseWindow
    {
        Entity *camera;
        sf::RenderWindow *window;
    };

    struct ClearWindow
    {
        Entity *camera;
    };

    class Window : public System
    {
        using Component = components::Window;

        struct RealWindow
        {
            sf::RenderWindow *win{nullptr};
            Component *data{nullptr};
            Component copy;
        };
        using WindowContainer = std::unordered_map<Component *, RealWindow>;
        enum States
        {
            INIT = 0,
            RUN
        };

        WindowContainer _windows;

        void updateTitle(RealWindow &real);
        void pollEvents(RealWindow &real);
        void open(RealWindow &);
        void close(RealWindow &);
        void requireEvents();
        void onWindowDestroyed(Component &);
        void onNewWindow(Component &);
        void init();
    public:
        Window(): System("Window") {}
        void run(float) override;
    };
}

#endif //FENGIN_WINDOW_HPP
