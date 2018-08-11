//
// Created by arroganz on 12/16/17.
//

#pragma once
# include "fengin-core/include/ecs.hpp"

namespace fengin {
    class Log : public System {
        int phase{0};

        void init();

    public:
        Log();

        void run(float) final;
    };
}