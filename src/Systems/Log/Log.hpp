//
// Created by arroganz on 12/16/17.
//

#ifndef FENGIN_LOG_HPP
#define FENGIN_LOG_HPP

#include "utils/ecs.hpp"

class Log : public futils::ISystem {
    int phase{0};
    void init();
public:
    Log();

    void run(float) final;
};

#endif //FENGIN_LOG_HPP
