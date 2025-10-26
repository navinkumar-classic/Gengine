//
// Created by navin on 10/23/25.
//

#include "MenuScene.h"
#include <iostream>

#include "../../Engine.h"

MenuScene::MenuScene(unsigned int width, unsigned int height) : Scene(width, height) {}

void MenuScene::init() {
    std::cout << "Initializing..." << std::endl;
}

void MenuScene::onExit(Engine& engine) {
    auto &window = engine.getWindow();

    window.setView(window.getDefaultView());

    for (const string& toDelete: eventsToDelete) {
        engine.event.deleteEvent(toDelete);
    }
    std::cout << "Exiting..." << std::endl;
}

void MenuScene::onResume() {
    std::cout << "Resuming..." << std::endl;
}

void MenuScene::onPause(Engine& engine) {
    auto &window = engine.getWindow();

    window.setView(window.getDefaultView());
    std::cout << "Pausing..." << std::endl;
}

void MenuScene::update(Engine& engine, float dt) {
    for (auto &uiElement: uiElements) {
        if (uiElement->getIsDynamic()) {
            uiElement->update(dt, engine.gameState, engine.input);
        }
    }
}

void MenuScene::render(Engine& engine) {

    auto &window = engine.getWindow();

    if (backgroundSet) {
        window.clear();
        window.setView(window.getDefaultView());
        window.draw(backgroundSprite);
    } else {
        window.clear(sf::Color::Black);
    }

    for (auto &uiElement: uiElements) {
        if (uiElement->getIsVisible()) {
            uiElement->render(window);
        }
    }

    window.display();
}