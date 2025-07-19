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
        const sf::Vector2f& size,
        const sf::Color& color):
        Entity(isMovable, position, velocity, gravity, maxSpeed, terminalVelocity, jumpStrength, acceleration, deacceleration),
        color(color)
{
    shape.setFillColor(color);
    shape.setPosition(position);
    setPreviousPosition(position);
    shape.setSize(size);
}

void StaticEntity::render(sf::RenderWindow& window) {
    window.draw(shape);
}

void StaticEntity::update(float dt, Input& input) {
    for (const auto& physicsFunction : physics) {
        physicsFunction(*this, input, dt);
    }

    applyMovement(dt);
    applyMovementToShape();
}

void StaticEntity::applyMovementToShape() {
    shape.setPosition(position);
}

sf::FloatRect StaticEntity::getBounds() const {
    return shape.getGlobalBounds();
}
