//
// Created by clara on 1/11/18.
//

#pragma once

#include "fengin-core/include/FenginCore.hpp"

namespace fengin::components
{
    class Text : public Component {
    public:
        futils::TextStyle   style;
        std::string         str;
    };
}