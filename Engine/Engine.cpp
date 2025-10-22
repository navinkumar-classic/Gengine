//
// Created by navin on 7/14/25.
//

#include "Engine.h"
#include "Entity/Entity.h"
#include "Physics/Collision/Collision.h"
#include <iostream>
#include <utility>

Engine::Engine(
    const string& fontPath,
    unsigned int width,
    unsigned int height):
    window(sf::VideoMode(width, height), "SFML Test"),
    camera(sf::FloatRect(0, 0, width, height)) {

    addFont("DEFAULT", fontPath);
}

void Engine::run() {
    while (isRunning) {
        float dt = clock.restart().asSeconds();
        processEvents(dt);
        update(dt);
        render();

        input.reset();

        if (cameraFunction) {
            cameraFunction(*trackingEntity, camera);
        }
    }
}

void Engine::processEvents(float dt) {
    sf::Event event{};
    vector<sf::Event> events;

    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed ||
           (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)) {
            isRunning = false;
            window.close();
           }

        events.push_back(event);
    }

    input.updateEvent(events, dt);
}

void Engine::update(float dt) {
    for (auto* entity : movableEntities) {
        if (entity->getIsAlive()) {
            entity->setPreviousPosition(entity->getPosition());
            entity->update(dt, input);
        }
    }

    for (auto* entity : animatedEntities) {
        if (entity->getIsAlive()) {
            entity->setPreviousPosition(entity->getPosition());
            entity->update(dt, input);
        }
    }
    collision.collisionManager(entities, movableEntities);

    for (auto& uiElement : uiElements) {
        if (uiElement->getIsDynamic()) {
            uiElement->update(dt, gameState);
        }
    }
}

void Engine::render() {

    if (backgroundSet) {
        window.clear();
        window.setView(window.getDefaultView());
        window.draw(backgroundSprite);
    } else {
        window.clear(sf::Color::Black);
    }

    window.setView(camera);
    for (auto& entity : entities) {
        if (entity->getIsAlive()) {
            entity->render(window);
        }
    }

    for (auto& uiElement : uiElements) {
        if (uiElement->getIsVisible()) {
            uiElement->render(window);
        }
    }

    window.display();
}

void Engine::addEntity(std::unique_ptr<Entity> entity) {
    if (entity->isMovable) {
        movableEntities.push_back(entity.get());
    }
    else if (entity->isAnimated) {
        animatedEntities.push_back(entity.get());
    }
    entities.push_back(std::move(entity));
}

void Engine::addUIElement(std::unique_ptr<UIElement> uiElement) {
    uiElements.push_back(std::move(uiElement));
}

void Engine::bindAction(const string& action, sf::Keyboard::Key key) {
    input.bindAction(action, key);
}

void Engine::setFrameRate(int frameRate) {
    window.setFramerateLimit(frameRate);
}

void Engine::addEntryToCollisionHandler(const string &a, const string &b, const std::function<void(Entity *a, Entity *b)> &handler) {
    collision.addEntryToCollisionHandler(a, b, handler);
}

void Engine::addCameraBehaviour(std::function<void(Entity&, sf::View&)> inputCameraFunction, int entity_id) {
    cameraFunction = std::move(inputCameraFunction);
    trackingEntity = entities[entity_id].get();
}

void Engine::setBackgroundTexture(const string& texturePath) {
    if (!backgroundTexture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load background.png\n";
    } else {
        backgroundSprite.setTexture(backgroundTexture);

        sf::Vector2u texSize = backgroundTexture.getSize();
        backgroundSprite.setScale(
            float(window.getSize().x) / texSize.x,
            float(window.getSize().y) / texSize.y
        );
    }

    backgroundSet = true;
}

void Engine::removeBackgroundTexture() {
    backgroundSet = false;
}

void Engine::addFont(const string& key, const string& fontPath) {
    sf::Font temp;
    temp.loadFromFile(fontPath);
    fonts[key] = temp;
}

const sf::Font& Engine::fetchFont(const string& key) {
    auto it = fonts.find(key);
    if (it != fonts.end()) {
        return it->second;
    }
    std::cerr << "Failed to find font for key " << key << "\n";

    return fonts["DEFAULT"];
}