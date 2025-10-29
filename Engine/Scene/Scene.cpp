//
// Created by navin on 10/23/25.
//

#include "Scene.h"
#include <string>
#include <iostream>

Scene::Scene(
    unsigned int width,
    unsigned int height):
    width(width),height(height){}


void Scene::addEventToDelete(const std::string& event) {
    eventsToDelete.push_back(event);
}

void Scene::setBackgroundTexture(const std::string &texturePath) {
    if (!backgroundTexture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load background.png\n";
    } else {
        backgroundSprite.setTexture(backgroundTexture);

        const sf::Vector2u texSize = backgroundTexture.getSize();
        backgroundSprite.setScale(
            static_cast<float>(width) / static_cast<float>(texSize.x),
            static_cast<float>(height) / static_cast<float>(texSize.y)
        );
    }

    backgroundSet = true;
}

void Scene::removeBackgroundTexture() {
    backgroundSet = false;
}

size_t Scene::addUIElement(std::unique_ptr<UIElement> uiElement) {
    uiElements.push_back(std::move(uiElement));

    return uiElements.size() - 1;
}

UIElement* Scene::getUIElement(size_t id) const {
    if (id >= uiElements.size()) return nullptr;
    return uiElements[id].get();
}

std::string Scene::getSceneUID() {
    return "scene_" + std::to_string(reinterpret_cast<uintptr_t>(this));
}
