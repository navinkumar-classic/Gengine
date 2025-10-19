//
// Created by navin on 7/15/25.
//

#include "StaticEntity.h"

StaticEntity::StaticEntity(
        bool isMovable,
        const sf::Vector2f& position,
        const sf::Vector2f& velocity,
        const sf::Vector2f& gravity,
        float maxSpeed,
        float terminalVelocity,
        float jumpStrength,
        float acceleration,
        float deacceleration,
        const sf::Vector2f& tileSize,
        const std::vector<std::vector<int>>& tilemat,
        const string& entityTag
        ):
        Entity(isMovable, position, velocity, gravity, maxSpeed, terminalVelocity, jumpStrength, acceleration, deacceleration, entityTag),
        tileMap(tileSize.x,tileSize.y)
{
    setPreviousPosition(position);
    tileMap.setPosition(position);
    tileMap.setMatrix(tilemat);
}

void StaticEntity::render(sf::RenderWindow& window) {
    tileMap.draw(window);
}

void StaticEntity::update(float dt, Input& input) {
    for (const auto& physicsFunction : physics) {
        physicsFunction(*this, input, dt);
    }

    applyMovement(dt);
    applyMovementToShape();
}

void StaticEntity::applyMovementToShape() {
    tileMap.setPosition(position);
}

sf::FloatRect StaticEntity::getBounds() const {
    return tileMap.getBounds();
}
