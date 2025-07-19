
#include <functional>
#include "Engine/Entity/EntityType/ControllableEntity.h"
#include "Engine/Entity/EntityType/StaticEntity.h"
#include "Engine/Actions/Movement.h"
#include "Engine/Engine.h"
#include "Engine/PhysicsSystem/EntityPhysics/EntityPhysics.h"


int main() {
    Engine engine(800,600);

    auto player = std::make_unique<ControllableEntity>(
        true,
        sf::Vector2f(200.0f, 150.0f),
        sf::Vector2f(0.0f, 0.0f),
        sf::Vector2f(0.0f, 1100.0f),
        300.0f,
        900.0f,
        -900.0f,
        750.0f,
        3000.0f,
        sf::Vector2u(800.0f, 600.0f),
        sf::Color::Red
    );
    player->addAction("UP", Movement::moveJump);
    player->addAction("RIGHT", Movement::moveRight);
    player->addAction("LEFT", Movement::moveLeft);

    player->addPhysics(EntityPhysics::applyGravity);
    player->addPhysics([](Entity& entity, Input& input, float dt){EntityPhysics::applyDeacceleration(entity, input, dt, "RIGHT", "LEFT");});

    engine.addEntity(std::move(player));

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
        sf::Vector2f(1500, 190),
        sf::Color::Green
    );

    engine.addEntity(std::move(wall1));

    auto wall2 = std::make_unique<StaticEntity>(
        true,
        sf::Vector2f(200, 0),
        sf::Vector2f(0.0f, 0.0f),
        sf::Vector2f(0.0f, 1100.0f),
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        sf::Vector2f(60, 60),
        sf::Color::Yellow
    );

    wall2->addPhysics(EntityPhysics::applyGravity);

    engine.addEntity(std::move(wall2));

    engine.run();

    return 0;
}
