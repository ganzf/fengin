//
// Created by arroganz on 8/3/18.
//

#include <Systems/SFML/Window.hpp>
#include <Systems/SFML/AssetLoader.hpp>
#include "IsoCam.hpp"
#include "Entities/Camera.hpp"
#include "Camera.hpp"

namespace fengin::systems::SFMLSystems {
    void IsoCam::init()
    {
        __init();
        addReaction<ResponseWindow>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<ResponseWindow>(pkg);
            camToWindow[packet.camera] = packet.window;
            auto worlds = entityManager->get<components::World>();
            if (worlds.empty())
                return ;
            auto unit = worlds.front()->unit;
            auto &transform = packet.camera->get<components::Transform>();
            transform.size.w = packet.window->getSize().x / unit;
            transform.size.h = packet.window->getSize().y / unit;
        });
        addReaction<fengin::events::RequestCamera>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<fengin::events::RequestCamera>(pkg);
            auto callback = packet.getCallback();
            if (knownCameras.find(packet.getName()) == knownCameras.end())
                return ;
            auto *cam = static_cast<fengin::entities::Camera *>(&knownCameras[packet.getName()]->getEntity());
            callback(cam);
        });
        phase = Run;
    }

    void IsoCam::renderWindow(futils::IEntity &cam)
    {
        auto win = camToWindow[&cam];
        if (win)
        {
            drawCamCrosshair(cam.get<components::Camera>(), win);
            win->display();
        }
    }

    void IsoCam::drawCamCrosshair(components::Camera &cam, sf::RenderWindow *window)
    {
        if (cam.debugMode == false)
            return;
        auto worlds = entityManager->get<components::World>();
        int crossHairSize = 10;
        if (!worlds.empty()) {
            auto &world = worlds.front();
            crossHairSize = world->unit / 2;
        }
        if (window != nullptr) {
            sf::Vertex vertical[] = {
                    sf::Vertex(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2 - crossHairSize)),
                    sf::Vertex(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2 + crossHairSize))
            };
            sf::Vertex horizontal[] = {
                    sf::Vertex(sf::Vector2f(window->getSize().x / 2 - crossHairSize, window->getSize().y / 2)),
                    sf::Vertex(sf::Vector2f(window->getSize().x / 2 + crossHairSize, window->getSize().y / 2))
            };
            window->draw(vertical, 2, sf::Lines);
            window->draw(horizontal, 2, sf::Lines);
        }
    }

    void IsoCam::renderCam(futils::IEntity &entity, components::Camera &cam, components::World &world)
    {
        RequestWindow request;
        request.camera = &entity;
        events->send<RequestWindow>(request);

        // camToWindow est update par la reaction a ResponseWindow
        auto realWindow = camToWindow[&entity];
        // Si tout va bien, on peut commencer a render, donc on clear.
        if (realWindow) {
            ClearWindow cw;
            cw.camera = &entity;
            events->send<ClearWindow>(cw);
        } else
        {
            events->send<std::string>("Cannot render because Camera system failed to find realWindow");
            return ;
        }
        auto &camPos = entity.get<components::Transform>();
        int currentLayer = -200;
        while (currentLayer < camPos.position.z + 200)
        {
            RenderLayer event;
            event.layer = currentLayer;
            event.camData = &cam;

            auto range = layout.equal_range(currentLayer);
            for (auto it = range.first; it != range.second; it++)
            {
//                auto &obj = it->second->get<components::GameObject>();
//                if (!obj.visible)
//                    continue ;

                auto &obj = it->second->get<components::GameObject>();
                if (!obj.visible)
                    continue ;
                auto &transform = it->second->get<components::Transform>();
                float zoom = 50;
                auto windowSize = realWindow->getSize();
                auto worldToScreen = [zoom, camPos, windowSize](vec3f world){
                    vec2f screen;
                    world.x *= zoom;
                    world.y *= zoom;
                    world.z *= zoom;
                    screen.x = world.x - world.y - camPos.position.x * zoom + windowSize.x / 2;
                    screen.y = (world.x + world.y) / 2 - camPos.position.y * zoom / 2 + windowSize.y / 2;
                    screen.y -= world.z;
                    return screen;
                };
                auto getBoundingBox = [](const components::Transform &tr){
                    std::vector<fengin::vec3f> points;
                    // TopSquare - 0
                    fengin::vec3f v = tr.position;
                    points.push_back(tr.position);
                    // TopAngle - 1
                    v.x = tr.position.x - tr.size.x;
                    v.y = tr.position.y - tr.size.y;
                    points.emplace_back(v);

                    // RightAngle - 2
                    v.x = tr.position.x;
                    v.y = tr.position.y - tr.size.y;
                    points.emplace_back(v);

                    // RightFace - 3
                    v.x = tr.position.x;
                    v.y = tr.position.y - tr.size.y;
                    v.z = tr.position.z - tr.size.z;
                    points.emplace_back(v);

                    // LeftFace
                    // BottomRight - 4
                    v.x = tr.position.x;
                    v.y = tr.position.y;
                    v.z = tr.position.z - tr.size.z;
                    points.emplace_back(v);
                    // BottomLeft - 5
                    v.x = tr.position.x - tr.size.x;
                    v.z = tr.position.z - tr.size.z;
                    points.emplace_back(v);

                    // LeftAngle - 6
                    v.x = tr.position.x - tr.size.x;
                    v.y = tr.position.y;
                    v.z = tr.position.z;
                    points.emplace_back(v);
                    return points;
                };
//                events->send<std::string>("IsoCam drawing : ");
//                events->send<fengin::components::Transform>(transform);
                auto drawPoint = [this, zoom, camPos, realWindow, worldToScreen, transform, windowSize](float deltaX, float deltaY, float deltaZ, sf::Color c) {
                    sf::CircleShape point(2);
                    point.setFillColor(sf::Color::Blue);
                    point.setOutlineThickness(1);
                    point.setOutlineColor(sf::Color::White);
                    vec3f world;
                    world.x = deltaX;
                    world.y = deltaY;
                    world.z = deltaZ;
                    auto screen = worldToScreen(world);
                    point.setPosition(screen.x, screen.y);
                    point.setFillColor(c);
                    realWindow->draw(point);
                };

                auto drawLine = [this, realWindow, worldToScreen](fengin::vec3f p1, fengin::vec3f p2, sf::Color c){
                    auto a = worldToScreen(p1);
                    auto b = worldToScreen(p2);
                    sf::Vertex line[] = {
                            sf::Vertex(sf::Vector2f(a.x, a.y), c),
                            sf::Vertex(sf::Vector2f(b.x, b.y), c),
                    };
                    realWindow->draw(line, 2, sf::Lines);
                };
                const auto box = getBoundingBox(transform);
//                for (auto const &p: box) {
//                    drawPoint(p.x, p.y, p.z, sf::Color::White);
//                }

                auto drawFace = [this, realWindow, worldToScreen](fengin::vec3f top, fengin::vec3f bottom, fengin::vec3f left, fengin::vec3f right, std::string const &path){
                    auto screenTop = worldToScreen(top);
                    auto screenBottom = worldToScreen(bottom);
                    auto screenLeft = worldToScreen(left);
                    auto screenRight = worldToScreen(right);
                    // Simple quad
                    sf::VertexArray face(sf::Quads, 4);
                    // Positions
                    face[0].position = sf::Vector2f(screenTop.x, screenTop.y);
                    face[1].position = sf::Vector2f(screenRight.x, screenRight.y);
                    face[2].position = sf::Vector2f(screenBottom.x, screenBottom.y);
                    face[3].position = sf::Vector2f(screenLeft.x, screenLeft.y);
                    // TexCoords not normalized (not between 0..1)
                    face[0].texCoords = sf::Vector2f(0, 0);
                    face[1].texCoords = sf::Vector2f(512, 0);
                    face[2].texCoords = sf::Vector2f(512, 512);
                    face[3].texCoords = sf::Vector2f(0, 512);
                    RequestTexture request;
                    request.path = path;
                    request.call = [this, realWindow, face](sf::Texture *texture){
                        if (texture)
                            realWindow->draw(face, texture);
                        else
                            realWindow->draw(face);
                    };
                    events->send<RequestTexture>(request);
                };

                drawFace(box[1], box[0], box[6], box[2], "grass.png");
                drawFace(box[6], box[4], box[5], box[3], "dirt1.jpg");
                drawFace(box[0], box[3], box[4], box[2], "dirt2.jpg");

                if (it->second->has<components::Border>()) {
                    const auto &border = it->second->get<components::Border>();
                    if (border.visible) {
                        sf::Color c;
                        c << border.color;
                        drawLine(box[0], box[6], c);
                        drawLine(box[6], box[1], c);
                        drawLine(box[1], box[2], c);
                        drawLine(box[0], box[2], c);
                        drawLine(box[3], box[2], c);
                        drawLine(box[3], box[4], c);
                        drawLine(box[4], box[5], c);
                        drawLine(box[5], box[6], c);
                        drawLine(box[0], box[4], c);
                    }
                }
                auto &absolute = it->second->get<components::AbsoluteTransform>();
                absolute.position.x = (int)worldToScreen(box[0]).x - 32;
                absolute.position.y = (int)worldToScreen(box[0]).y - 32;
                absolute.size.w = 64;
                absolute.size.h = 64;
//                auto &absolute = it->second->get<components::AbsoluteTransform>();
//                auto &transform = it->second->get<components::Transform>();
//                auto windowSize = realWindow->getSize();
//                auto unit = world.unit;
//                auto zoom = 1; // TODO : add zoom
//
//                absolute.position.x = (int)(windowSize.x / 2 + (transform.position.x - camPos.position.x) * unit * zoom);
//                absolute.position.y = (int)(windowSize.y / 2 + (transform.position.y - camPos.position.y) * unit * zoom);
//                absolute.size.x = (int)(transform.size.x * unit * zoom);
//                absolute.size.y = (int)(transform.size.y * unit * zoom);
//
//                if (absolute.position.x < (int) windowSize.x
//                    && absolute.position.x + absolute.size.x > 0
//                    && absolute.position.y < (int)windowSize.y
//                    && absolute.size.y + absolute.position.y > 0) {
//
//                    event.objects.push_back(it->second);
//                }
            }
            event.window = realWindow;
            events->send<RenderLayer>(event);
            currentLayer++;
        }
        AllLayersRendered allLayersRendered;
        allLayersRendered.camData = &cam;
        allLayersRendered.window = realWindow;
        events->send<AllLayersRendered>(allLayersRendered);
        renderWindow(entity);
    }

    void IsoCam::renderEachCam() {
        auto cameras = entityManager->get<components::Camera>();
        auto worlds = entityManager->get<components::World>();

        if (worlds.empty())
            return ;
        auto &world = worlds.front();
        knownCameras.clear();
        for (auto &cam: cameras)
        {
            auto &entity = cam->getEntity();
            knownCameras[cam->name] = cam;
            if (cam->activated && cam->window) {
                renderCam(entity, *cam, *world);
            }
        }
    }

    void IsoCam::sortGameObjects() {
        layout.clear();
        auto gameObjects = entityManager->get<components::GameObject>();
        auto nearness = [](components::Transform const &tr){
            return (int)(tr.position.x + tr.position.y + tr.position.z);
        };
//        auto aCloserThanB = [nearness](components::Transform const &a, components::Transform const &b) {
//            return nearness(a) > nearness(b);
//        };
        for (auto &go: gameObjects)
        {
            auto &entity = go->getEntity();
            if (!entity.has<components::Transform>())
                throw std::logic_error("Game object missing transform component in [Camera].");
            auto &transform = entity.get<components::Transform>();
            layout.insert(std::pair<int, futils::IEntity *>(nearness(transform), &entity));
        }
    }

    void IsoCam::run(float e) {
        static float t = 0.0;
        t+=e;
        switch (phase)
        {
            case Init: return init();
            case Run:
                events->send<StartingRendering>();
                sortGameObjects();
                if (t >= 0.02)
                    t = 0.0;
                if (t == 0.0)
                    renderEachCam();
                return ;
        }
    }
}