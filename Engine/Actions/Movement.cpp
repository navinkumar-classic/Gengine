//
// Created by navin on 7/15/25.
//

#include "Movement .h"

void Movement::moveLeft(sf::Vector2f& position, sf::Vector2f& velocity, float dt, float maxSpeed, float acceleration, float deacceleration, bool& onGround, float jumpStrength,  Input& input, string action){
    if (input.isActionHeld(action)) {
        velocity.x -= acceleration * dt;
        if (velocity.x < -maxSpeed)
            velocity.x = -maxSpeed;
    }
}

void Movement::moveRight(sf::Vector2f& position, sf::Vector2f& velocity, float dt, float maxSpeed, float acceleration, float deacceleration, bool& onGround, float jumpStrength,  Input& input, string action) {
    if (input.isActionHeld(action)) {
        velocity.x += acceleration * dt;
        if (velocity.x > maxSpeed)
            velocity.x = maxSpeed;
    }
}

void Movement::moveJump(sf::Vector2f& position, sf::Vector2f& velocity, float dt, float maxSpeed, float acceleration, float deacceleration, bool& onGround, float jumpStrength,  Input& input, string action) {
    if (input.isActionHeld(action)) {
        if (onGround == true) {
            velocity.y = jumpStrength;
            onGround = false;
        }
    }
}

void Movement::applyDeacceleration(sf::Vector2f& velocity, float dt, float deacceleration, bool& onGround, Input& input, string action1, string action2) {
    bool movingLeft = input.isActionHeld(action1);
    bool movingRight = input.isActionHeld(action2);

    if (!movingLeft && !movingRight && onGround) {
        if (velocity.x > 0) {
            velocity.x -= deacceleration * dt;
            if (velocity.x < 0)
                velocity.x = 0;
        } else if (velocity.x < 0) {
            velocity.x += deacceleration * dt;
            if (velocity.x > 0)
                velocity.x = 0;
        }
    }
}

void Movement::applyMovement(sf::Vector2f& position, sf::Vector2f& velocity, float dt) {
    position += velocity * dt;
}
