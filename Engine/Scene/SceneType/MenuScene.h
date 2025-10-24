//
// Created by navin on 10/23/25.
//

#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Scene.h"
#include "../../UIElement/UIElement.h"

class MenuScene: public Scene {
    public:
        explicit MenuScene(unsigned int width, unsigned int height);

        void init() override;

        void onExit(Engine& engine) override;

        void onResume() override;

        void onPause(Engine& engine) override;

        void update(Engine& engine, float dt) override;

        void render(Engine& engine) override;

        size_t addUIElement(std::unique_ptr<UIElement> uiElement);

        UIElement* getUIElement(size_t index) const;

        void setBackgroundTexture(const std::string& texturePath);

        void removeBackgroundTexture();

    private:
        unsigned int width;
        unsigned int height;

        std::vector<std::unique_ptr<UIElement>> uiElements;

        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        bool backgroundSet = false;
};
