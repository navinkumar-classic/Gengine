//
// Created by navin on 10/23/25.
//
#pragma once
class Engine;
#include <vector>
#include <string>
#include "../Event/EventManager.h"

class Scene {
    public:
        virtual ~Scene() = default;

        virtual void init() = 0;
        virtual void onResume() = 0;
        virtual void onPause(Engine& engine) = 0;
        virtual void onExit(Engine& engine) = 0;

        virtual void update(Engine& engine, float dt) = 0;
        virtual void render(Engine& engine) = 0;

        void addEventToDelete(const std::string& event);

    protected:
        std::vector<std::string> eventsToDelete;

};
