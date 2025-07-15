//
// Created by navin on 7/14/25.
//

#include "Engine.h"
#include "Entity/EntityType/ControllableEntity.h"
#include "Entity/EntityType/StaticEntity.h"
#include "System/Collision.h"
#include <iostream>

Engine::Engine(unsigned int width, unsigned int height)
    : window(sf::VideoMode(width, height), "SFML Test")
{
    input.bindAction("RIGHT",sf::Keyboard::Right);
    input.bindAction("LEFT",sf::Keyboard::Left);
    input.bindAction("UP",sf::Keyboard::Up);
    input.bindAction("DOWN",sf::Keyboard::Down);

    std::vector<std::string> actions = {
        "UP", "DOWN", "LEFT", "RIGHT"
    };

    auto player = std::make_unique<ControllableEntity>(
        150.f,
        sf::Vector2f(100, 100),
        window.getSize(),
        sf::Color::Red,
        actions,
        true
    );

    entities.push_back(std::move(player));

    auto wall1 = std::make_unique<StaticEntity>(
        sf::Vector2f(0, 300),
        sf::Vector2f(800, 50),
        sf::Color::Green
    );

    entities.push_back(std::move(wall1));

    setMovableEntities();

}

void Engine::run() {

    while (isRunning) {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }

}

void Engine::processEvents() {
    sf::Event event{};
    vector<sf::Event> events;

    while (window.pollEvent(event)) {
        // Close window or press ESC
        if (event.type == sf::Event::Closed ||
           (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)) {
            isRunning = false;
            window.close();
           }

        events.push_back(event);
    }

    input.updateEvent(events);
}

void Engine::update(float dt) {
    for (auto* entity : movableEntities) {
            entity->update(dt, input);
    }
    input.reset();

    Collision::detectCollision(entities, movableEntities);
}

void Engine::render() {
    window.clear(sf::Color::Black);

    for (auto& entity : entities)
        entity->render(window);

    window.display();
}

void Engine::setMovableEntities() {
    for (auto& entity : entities) {
        if (entity->isMovable) {
            movableEntities.push_back(entity.get());
        }
    }
}
