//
// Created by navin on 7/14/25.
//
#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Input/Input.h"
#include "Entity/Entity.h"

class Engine {
public:
    Engine(unsigned int width = 800, unsigned int height = 600);
    void run();
    void addEntity(unique_ptr<Entity> entity);

private:
    void processEvents(float dt);
    void update(float dt);
    void render();

    bool isRunning = true;

    sf::RenderWindow window;
    sf::View camera;
    sf::Clock clock;
    Input input;
    std::vector<unique_ptr<Entity>> entities;
    std::vector<Entity*> movableEntities;
};
