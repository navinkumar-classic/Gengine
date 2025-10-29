//
// Created by navin on 7/15/25.
//

#include "ControllableEntity.h"
#include <utility>

#include "../../../Utility/Movement.h"
#include "../../../Utility/EntityPhysics.h"
#include "../../Engine.h"

ControllableEntity::ControllableEntity(
        bool isMovable,
        const sf::Vector2f& position,
        const sf::Vector2f& velocity,
        const sf::Vector2f& gravity,
        float maxSpeed,
        float terminalVelocity,
        float jumpStrength,
        float acceleration,
        float deacceleration,
        sf::Vector2u windowSize,
        int frameWidth,
        int frameHeight,
        float frameDuration,
        const sf::Vector2f& scale,
        const string& entityTag
        ):
        Entity(true, isMovable, position, velocity, gravity, maxSpeed, terminalVelocity, jumpStrength, acceleration, deacceleration, entityTag),
        windowSize(windowSize),
        Sprite(frameWidth, frameHeight, frameDuration, scale)
{
    setPreviousPosition(position);
    Sprite.setPosition(position);
}
void ControllableEntity::update(float dt, Engine& engine) {

    for (const auto& action : action) {
        action.second(*this, engine.input, engine.music, action.first, dt);
    }

    for (const auto& physicsFunction : physics) {
        physicsFunction(*this, engine.input, dt);
    }

    applyMovement(dt);
    applyMovementToShape();
    Sprite.update(dt);
}

void ControllableEntity::render(sf::RenderWindow& window) {

    Sprite.draw(window);
}

void ControllableEntity::applyMovementToShape() {

    Sprite.setPosition(position);
}

void ControllableEntity::addAction(string action, const function<void(ControllableEntity& entity, InputManager& input, MusicManager& music, string action, float dt)>& func) {
    ControllableEntity::action.emplace_back(action, func);
}

void ControllableEntity::clearActions() {
    ControllableEntity::action.clear();
}

sf::FloatRect ControllableEntity::getBounds() const {
    return Sprite.getBounds();
}