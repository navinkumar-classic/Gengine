//
// Created by navin on 10/23/25.
//

#pragma once

#include "../Scene.h"

class MenuScene: public Scene {
    public:
        explicit MenuScene(unsigned int width, unsigned int height);

        void init() override;

        void onExit(Engine& engine) override;

        void onResume() override;

        void onPause(Engine& engine) override;

        void update(Engine& engine, float dt) override;

        void render(Engine& engine) override;

};
