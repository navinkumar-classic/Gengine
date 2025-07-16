//
// Created by navin on 7/15/25.
//

#include "ControllableEntity.h"
#include <utility>
#include <iostream>

#include "../../Actions/Movement .h"

ControllableEntity::ControllableEntity(float speed, const sf::Vector2f &position, sf::Vector2u windowSize,
    vector<std::pair<string, function<void(sf::Vector2f&, sf::Vector2f&, float, float, float, float, bool&, float, Input& input, string action)>>> actions, const sf::Color &color):
Entity(speed, position, true, true, true), color(color), action(std::move(actions)), windowSize(windowSize) {
    shape.setSize({32, 32});
    shape.setFillColor(color);
    shape.setPosition(position);
    setPreviousPosition(position);
}
void ControllableEntity::update(float dt, Input& input) {

    for (const auto& action : action) {
        action.second(position, velocity, dt, maxSpeed, acceleration, deacceleration, onGround, jumpStrength, input, action.first);
    }


    Movement::applyDeacceleration(velocity, dt, deacceleration, onGround, input, "LEFT", "RIGHT");

    applyGravity(dt);
    Movement::applyMovement(position, velocity, dt);
    shape.setPosition(position);
}

void ControllableEntity::render(sf::RenderWindow& window) {
    window.draw(shape);
}

void ControllableEntity::applyGravity(float dt) {
    if ( gravityEnabled ) {

        if (onGround == false) {

            if (velocity.y < 0) {
                velocity.y += 2*gravity.y * dt;
            }
            else {
                velocity.y += gravity.y * dt;
            }
        }
        else {
            velocity.y = 0;
        }
        onGround = false;
    }
}

void ControllableEntity::addAction(string& action, function<void(sf::Vector2f&, sf::Vector2f&, float, float, float, float, bool&, float, Input& input, string action)>& func) {
    ControllableEntity::action.emplace_back(action, func);
}

void ControllableEntity::clearActions() {
    ControllableEntity::action.clear();
}

sf::FloatRect ControllableEntity::getBounds() const {
    return shape.getGlobalBounds();
}