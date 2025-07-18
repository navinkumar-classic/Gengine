//
// Created by navin on 7/18/25.
//

#include "EntityPhysics.h"

void EntityPhysics::applyGravity(Entity& entity, Input& input, float dt) {
    if (entity.getVelocity().y < 0) {
        entity.setVerticalVelocity(entity.getVelocity().y + 2 * entity.getGravity().y * dt);
    }
    else {
        entity.setVerticalVelocity(entity.getVelocity().y + 2 * entity.getGravity().y * dt);
    }
    //entity.setOnGround(false);
}

void EntityPhysics::applyDeacceleration(Entity& entity, Input& input, float dt, string action1, string action2) {
    bool movingLeft = input.isActionHeld(action1);
    bool movingRight = input.isActionHeld(action2);

    if (!movingLeft && !movingRight && entity.getOnGround()) {
        if (entity.getVelocity().x > 0) {
            entity.setHorizontalVelocity(entity.getVelocity().x - entity.getDeacceleration() * dt);
            if (entity.getVelocity().x < 0)
                entity.setHorizontalVelocity(0);
        } else if (entity.getVelocity().x < 0) {
            entity.setHorizontalVelocity(entity.getVelocity().x + entity.getDeacceleration() * dt);
            if (entity.getVelocity().x > 0)
                entity.setHorizontalVelocity(0);
        }
    }
}