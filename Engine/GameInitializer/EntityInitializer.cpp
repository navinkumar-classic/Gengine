//
// Created by navin on 7/15/25.
//
#include "EntityInitializer.h"

#include "../Actions/Movement .h"
#include "../Entity/EntityType/ControllableEntity.h"
#include "../Entity/EntityType/StaticEntity.h"

std::vector<std::unique_ptr<Entity>> EntityInitializer::CreateEntityInitialization(sf::Vector2u windowSize) {
    std::vector<std::unique_ptr<Entity>> entities;

    std::vector<std::pair<std::string, function<void(ControllableEntity&, Input&, string, float )>>> actions = {};

    actions.emplace_back("LEFT", Movement::moveLeft);
    actions.emplace_back("RIGHT", Movement::moveRight);
    actions.emplace_back("UP", Movement::moveJump);

    auto player = std::make_unique<ControllableEntity>(
        true,
        sf::Vector2f(100.0f, 200.0f),
        sf::Vector2f(0.0f, 0.0f),
        sf::Vector2f(0.0f, 1100.0f),
        500.0f,
        900.0f,
        -900.0f,
        750.0f,
        2000.0f,
        windowSize,
        actions,
        sf::Color::Red
    );

    entities.push_back(std::move(player));

    auto wall1 = std::make_unique<StaticEntity>(
        false,
        sf::Vector2f(0, 300),
        sf::Vector2f(0.0f, 0.0f),
        sf::Vector2f(0.0f, 0.0f),
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        sf::Vector2f(600, 190),
        sf::Color::Green
    );

    entities.push_back(std::move(wall1));

    auto wall2 = std::make_unique<StaticEntity>(
        false,
        sf::Vector2f(50, 250),
        sf::Vector2f(0.0f, 0.0f),
        sf::Vector2f(0.0f, 0.0f),
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        sf::Vector2f(400, 40),
        sf::Color::Green
    );

    entities.push_back(std::move(wall2));

    return entities;
}
