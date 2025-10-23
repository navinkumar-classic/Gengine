//
// Created by navin on 10/23/25.
//
#pragma once

class Engine;
class Scene {
    public:
        virtual ~Scene() = default;

        virtual void init() = 0;
        virtual void onPause() = 0;
        virtual void onExit() = 0;

        virtual void update(Engine& engine, float dt) = 0;
        virtual void render(Engine& engine) = 0;

};
