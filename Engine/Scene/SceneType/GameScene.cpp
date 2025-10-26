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
    unsigned int height) : camera(sf::FloatRect(0, 0, static_cast<float>(width), static_cast<float>(height))),
                           trackingEntity(nullptr), Scene(width, height){}

void GameScene::init() {
    std::cout << "Initializing..." << std::endl;
}

void GameScene::onResume() {
    std::cout << "Resuming..." << std::endl;
}

void GameScene::onExit(Engine& engine) {
    auto &window = engine.getWindow();

    window.setView(window.getDefaultView());

    for (const string& toDelete: eventsToDelete) {
        engine.event.deleteEvent(toDelete);
    }
    std::cout << "Exiting..." << std::endl;
}

void GameScene::onPause(Engine& engine) {
    auto &window = engine.getWindow();

    window.setView(window.getDefaultView());
    std::cout << "Pausing..." << std::endl;
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
            uiElement->update(dt, engine.gameState, engine.input);
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

Entity *GameScene::getEntity(size_t id) const {
    if (id >= entities.size()) return nullptr;
    return entities[id].get();
}

void GameScene::addCameraBehaviour(std::function<void(Entity &, sf::View &)> inputCameraFunction, size_t entity_id) {
    cameraFunction = std::move(inputCameraFunction);
    trackingEntity = entities[entity_id].get();
}