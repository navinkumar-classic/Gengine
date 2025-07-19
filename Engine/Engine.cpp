//
// Created by navin on 7/14/25.
//

#include "Engine.h"
#include "Entity/Entity.h"
#include "PhysicsSystem/Collision/Collision.h"
#include <iostream>
#include "CameraSystem/CameraBehaviour.h"

Engine::Engine(unsigned int width, unsigned int height)
    : window(sf::VideoMode(width, height), "SFML Test"),
        camera(sf::FloatRect(0, 0, width, height))
{
    window.setFramerateLimit(120);
    input.bindAction("RIGHT",sf::Keyboard::D);
    input.bindAction("LEFT",sf::Keyboard::A);
    input.bindAction("UP",sf::Keyboard::Space);
}

void Engine::run() {
    while (isRunning) {
        float dt = clock.restart().asSeconds();
        processEvents(dt);
        update(dt);
        render();

        input.reset();
        cameraBehaviour::cameraTracking(*entities[0], camera, 200.0f, 2000.0f);
        window.setView(camera);
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
            entity->setPreviousPosition(entity->getPosition());
            entity->update(dt, input);
    }
    Collision::detectCollision(entities, movableEntities);
}

void Engine::render() {
    window.clear(sf::Color::Black);

    for (auto& entity : entities)
        entity->render(window);

    window.display();
}

void Engine::addEntity(std::unique_ptr<Entity> entity) {
    if (entity->isMovable) {
        movableEntities.push_back(entity.get());
    }
    entities.push_back(std::move(entity));
}
