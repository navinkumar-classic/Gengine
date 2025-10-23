//
// Created by navin on 7/14/25.
//

#include "GameScene.h"
#include "../../Entity/Entity.h"
#include "../../Physics/Collision/Collision.h"
#include <iostream>
#include <utility>

#include "../../Engine.h"

GameScene::GameScene(
    unsigned int width,
    unsigned int height) : camera(sf::FloatRect(0, 0, width, height)),
                           trackingEntity(nullptr), width(width), height(height) {
}

void GameScene::update(Engine &engine, const float dt) {
    for (auto *entity: movableEntities) {
        if (entity->getIsAlive()) {
            entity->setPreviousPosition(entity->getPosition());
            entity->update(dt, engine.input);
        }
    }

    for (auto *entity: animatedEntities) {
        if (entity->getIsAlive()) {
            entity->setPreviousPosition(entity->getPosition());
            entity->update(dt, engine.input);
        }
    }

    for (auto &uiElement: uiElements) {
        if (uiElement->getIsDynamic()) {
            uiElement->update(dt, engine.gameState);
        }
    }

    if (cameraFunction) {
        cameraFunction(*trackingEntity, camera);
    }

    engine.collision.collisionManager(entities, movableEntities);
}

void GameScene::render(Engine &engine) {
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

    window.setView(camera);

    for (auto &entity: entities) {
        if (entity->getIsAlive()) {
            entity->render(window);
        }
    }

    window.display();
}

size_t GameScene::addEntity(std::unique_ptr<Entity> entity) {
    if (entity->isMovable) {
        movableEntities.push_back(entity.get());
    } else if (entity->isAnimated) {
        animatedEntities.push_back(entity.get());
    }
    entities.push_back(std::move(entity));

    return entities.size() - 1;
}

void GameScene::addUIElement(std::unique_ptr<UIElement> uiElement) {
    uiElements.push_back(std::move(uiElement));
}

void GameScene::addCameraBehaviour(std::function<void(Entity &, sf::View &)> inputCameraFunction, size_t entity_id) {
    cameraFunction = std::move(inputCameraFunction);
    trackingEntity = entities[entity_id].get();
}

void GameScene::setBackgroundTexture(const string &texturePath) {
    if (!backgroundTexture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load background.png\n";
    } else {
        backgroundSprite.setTexture(backgroundTexture);

        const sf::Vector2u texSize = backgroundTexture.getSize();
        backgroundSprite.setScale(
            static_cast<float>(width) / texSize.x,
            static_cast<float>(height) / texSize.y
        );
    }

    backgroundSet = true;
}

void GameScene::removeBackgroundTexture() {
    backgroundSet = false;
}

Entity *GameScene::getEntity(size_t id) const {
    if (id >= entities.size()) return nullptr;
    return entities[id].get();
}

void GameScene::init() {
    std::cout << "Initializing..." << std::endl;
}

void GameScene::onExit() {
    std::cout << "Exiting..." << std::endl;
}

void GameScene::onPause() {
    std::cout << "Pausing..." << std::endl;
}