//
// Created by navin on 7/15/25.
//
#include "EntityInitializer.h"

#include "../Actions/Movement .h"
#include "../Entity/EntityType/ControllableEntity.h"
#include "../Entity/EntityType/StaticEntity.h"

std::vector<std::unique_ptr<Entity>> EntityInitializer::CreateEntityInitialization(sf::Vector2u windowSize) {
    std::vector<std::unique_ptr<Entity>> entities;

    std::vector<std::pair<std::string, function<void(sf::Vector2f&, sf::Vector2f&, float, float, float, float, bool&, float, Input&, string)>>> actions = {};

    actions.emplace_back("LEFT", Movement::moveLeft);
    actions.emplace_back("RIGHT", Movement::moveRight);
    actions.emplace_back("UP", Movement::moveJump);

    auto player = std::make_unique<ControllableEntity>(
        150.f,
        sf::Vector2f(100, 200),
        windowSize,
        actions,
        sf::Color::Red
    );

    entities.push_back(std::move(player));

    auto wall1 = std::make_unique<StaticEntity>(
        sf::Vector2f(0, 300),
        sf::Vector2f(600, 190),
        sf::Color::Green
    );

    entities.push_back(std::move(wall1));

    auto wall2 = std::make_unique<StaticEntity>(
        sf::Vector2f(0, 100),
        sf::Vector2f(400, 90),
        sf::Color::Green
    );

    entities.push_back(std::move(wall2));

    return entities;
}
