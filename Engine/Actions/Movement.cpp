//
// Created by navin on 7/15/25.
//

#include "Movement .h"
#include <iostream>

void Movement::moveLeft(ControllableEntity& entity, Input& input, string action, float dt){
    if (input.isActionHeld(action)) {
        entity.setHorizontalVelocity(entity.getVelocity().x - entity.getAcceleration() * dt);
        if (entity.getVelocity().x < -entity.getMaxSpeed())
            entity.setHorizontalVelocity(-entity.getMaxSpeed());
    }
}

void Movement::moveRight(ControllableEntity& entity, Input& input, string action, float dt) {
    if (input.isActionHeld(action)) {
        entity.setHorizontalVelocity(entity.getVelocity().x + entity.getAcceleration() * dt);
        if (entity.getVelocity().x > entity.getMaxSpeed())
            entity.setHorizontalVelocity(entity.getMaxSpeed());
    }
}

void Movement::moveJump(ControllableEntity& entity, Input& input, string action, float dt) {
    cout << entity.getOnGround() << endl;
    if (input.wasActionPressed(action) && entity.getOnGround()) {
        entity.setVerticalVelocity(entity.getJumpStrength());
        entity.setOnGround(false);
        entity.setJump(true);
    }
    if (entity.getOnGround() == false && entity.getJump() && !input.isActionHeld(action)) {
        entity.setVerticalVelocity(entity.getVelocity().y * 0.5f);
        entity.setJump(false);
    }
}