//
// Created by navin on 7/15/25.
//

#include "ControllableEntity.h"
#include <utility>

#include "../../Actions/Movement .h"
#include "../../PhysicsSystem/EntityPhysics/EntityPhysics.h"

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
        vector<std::pair<string, function<void(ControllableEntity& entity, Input& input, string action, float dt)>>> actions,
        const sf::Color& color
        ):
        Entity(isMovable, position, velocity, gravity, maxSpeed, terminalVelocity, jumpStrength, acceleration, deacceleration),
        color(color),
        action(std::move(actions)),
        windowSize(windowSize)
{
    shape.setSize({32, 32});
    shape.setFillColor(color);
    shape.setPosition(position);
    setPreviousPosition(position);
}
void ControllableEntity::update(float dt, Input& input) {

    for (const auto& action : action) {
        action.second(*this, input, action.first, dt);
    }

    EntityPhysics::applyDeacceleration(*this, input, dt, "LEFT", "RIGHT");
    EntityPhysics::applyGravity(*this, input, dt);

    applyMovement(dt);
    applyMovementToShape();
}

void ControllableEntity::render(sf::RenderWindow& window) {
    window.draw(shape);
}

void ControllableEntity::applyMovementToShape() {
    shape.setPosition(position);
}

void ControllableEntity::addAction(string& action, function<void(ControllableEntity& entity, Input& input, string action, float dt)>& func) {
    ControllableEntity::action.emplace_back(action, func);
}

void ControllableEntity::clearActions() {
    ControllableEntity::action.clear();
}

sf::FloatRect ControllableEntity::getBounds() const {
    return shape.getGlobalBounds();
}