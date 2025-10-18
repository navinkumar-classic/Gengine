//
// Created by navin on 7/15/25.
//

#include "Movement.h"
#include <iostream>

void Movement::moveLeft(ControllableEntity& entity, Input& input, string action, float dt){
    if (input.isActionHeld(action)) {
        entity.setHorizontalVelocity(entity.getVelocity().x - entity.getAcceleration() * dt);
        if (entity.getVelocity().x < -entity.getMaxSpeed())
            entity.setHorizontalVelocity(-entity.getMaxSpeed());

        entity.Sprite.flipToLeft();
        if (entity.Sprite.getCurrentAction() != "WALK" && entity.getOnGround())
            entity.Sprite.setTextureToSprite("WALK");
    }
}

void Movement::moveRight(ControllableEntity& entity, Input& input, string action, float dt) {
    if (input.isActionHeld(action)) {
        entity.setHorizontalVelocity(entity.getVelocity().x + entity.getAcceleration() * dt);
        if (entity.getVelocity().x > entity.getMaxSpeed())
            entity.setHorizontalVelocity(entity.getMaxSpeed());

        entity.Sprite.flipToRight();
        if (entity.Sprite.getCurrentAction() != "WALK" && entity.getOnGround())
            entity.Sprite.setTextureToSprite("WALK");

    }
}

void Movement::moveJump(ControllableEntity& entity, Input& input, string action, float dt) {
    if (input.wasActionPressed(action) && entity.getOnGround()) {
        entity.setVerticalVelocity(entity.getJumpStrength());
        entity.setOnGround(false);
        entity.setJump(true);
        if (entity.Sprite.getCurrentAction() != "JUMP")
            entity.Sprite.setTextureToSprite("JUMP");
    }
    if (entity.getOnGround() == false && entity.getJump() && !input.isActionHeld(action)) {
        entity.setVerticalVelocity(entity.getVelocity().y * 0.5f);
        entity.setJump(false);
    }
}