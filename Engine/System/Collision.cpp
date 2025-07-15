//
// Created by navin on 7/15/25.
//

#include "Collision.h"
#include <iostream>

void Collision::detectCollision(const std::vector<std::unique_ptr<Entity>>& entities,const std::vector<Entity*>& movableEntities) {
    for (auto* entityA : movableEntities) {
        for (auto& entityB : entities ) {
            if (entityA == entityB.get()) continue;

            if (checkCollision(entityA, entityB.get())) {
                handleCollision(entityA, entityB.get());
            }
        }
    }
}

void Collision::handleCollision(Entity* a, Entity* b) {
    if (a->isMovable && !b->isMovable) {
        a->setPosition(a->getPreviousPosition());
    } else if (!a->isMovable && b->isMovable) {
        b->setPosition(b->getPreviousPosition());
    } else if (a->isMovable && b->isMovable) {
        // Both movable: for now, just push both back
        a->setPosition(a->getPreviousPosition());
        b->setPosition(b->getPreviousPosition());
    }
}

bool Collision::checkCollision(const Entity* a, const Entity* b) {
    return a->getBounds().intersects(b->getBounds());
}
