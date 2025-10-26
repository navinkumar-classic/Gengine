//
// Created by navin on 10/23/25.
//
#pragma once
#include <memory>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "../UIElement/UIElement.h"

class Engine;

class Scene {
    public:
        Scene(unsigned int width, unsigned int height);
        virtual ~Scene() = default;

        virtual void init() = 0;
        virtual void onResume() = 0;
        virtual void onPause(Engine& engine) = 0;
        virtual void onExit(Engine& engine) = 0;

        virtual void update(Engine& engine, float dt) = 0;
        virtual void render(Engine& engine) = 0;

        void addEventToDelete(const std::string& event);
        void setBackgroundTexture(const std::string& texturePath);
        void removeBackgroundTexture();

        size_t addUIElement(std::unique_ptr<UIElement> uiElement);
        UIElement* getUIElement(size_t index) const;

    protected:
        unsigned int width;
        unsigned int height;

        std::vector<std::string> eventsToDelete;

        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        bool backgroundSet = false;

        std::vector<std::unique_ptr<UIElement>> uiElements;

};
