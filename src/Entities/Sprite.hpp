//
// Created by clara on 1/28/18.
//



#pragma once

#include <Components/Sprite.hpp>
#include "GameObject.hpp"
#include "Image.hpp"

namespace fengin::entities {

    class Sprite : public GameObject {

    public:
        Sprite(float speed, bool loop = true) {
            auto &sprite = attach<fengin::components::Sprite>();
            attach<fengin::components::Image>();
            sprite.speed = speed;
            sprite.loop = loop;
        }

        void autoLoad(std::string const &file,
                      futils::Vec2<int> gridNbr,
                      futils::Vec2<int> gridSize)
        {
            auto &sprites = get<fengin::components::Sprite>();
            sprites.autoLoad(file, gridNbr, gridSize);
        }

        void addSprite(std::string const &file,
                       futils::Vec2<int> pos = futils::Vec2<int>(0, 0),
                       futils::Vec2<int> size = futils::Vec2<int>(-1, -1)) {
            auto &sprites = get<fengin::components::Sprite>();
            sprites.addSprite(file, pos, size);
        }

        ~Sprite() {
            detach<components::Sprite>();
            detach<components::Image>();
        }
    };
}