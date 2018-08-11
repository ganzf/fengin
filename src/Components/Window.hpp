//
// Created by arroganz on 12/18/17.
//

#pragma once

# include "fengin-core/include/FenginCore.hpp"

namespace fengin::components {
    struct Window : Component {
        std::string title;
        // TODO: futils::Asset
        // futils::Asset icon;
        futils::WStyle style;
        // TODO: futils::dim2d<> ?
        vec2f position{0, 0};
        vec2f size{};
        bool visible{false};

        // updated by [Window]
        void *_actualWindow;
        vec2f actualPosition;
        vec2f actualSize;
        vec2f screenSize;
        bool isOpen{false};
        bool isClose{false};
    };

    inline std::ostream &operator << (std::ostream &os, Window const &m)
    {
        os << "(Window) : " << m.title << std::endl;
        return os;
    }
}
