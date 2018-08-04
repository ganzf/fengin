//
// Created by arroganz on 2018-07-31
//

#pragma once
# include "fengin-core/include/events.hpp"
# include "utils/ecs.hpp"

class Fysix : public futils::ISystem {
    enum State
    {
        Init = 0,
        Run
    };
    State state{Init};
    void init();
public:
    Fysix();

    void run(float) final;
};
