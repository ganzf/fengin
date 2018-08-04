//
// Created by arroganz on 2018-07-29
//

#pragma once

// TODO: Change CMAKELISTS.TXT to make this compile :)
# include <SFML/Graphics.hpp>

# include "utils/ecs.hpp"
# include "fengin-core/include/events.hpp"
# include "utils/rendering.hpp"
# include "System.hpp"

namespace fengin::systems {
    class SFMLRenderer : public futils::ISystem {
        enum State
        {
            NONE = -1,
            INIT = 0,
            RENDER
        };
        State state{INIT};

        void requireEvents();
        void init();
    public:
        SFMLRenderer();
        void run(float) final;
    };
}