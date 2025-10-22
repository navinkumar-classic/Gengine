//
// Created by navin on 7/15/25.
//

#include "Collision.h"
#include <iostream>

#include "../../../Util/CollisionBehaviour.h"

void Collision::collisionManager(const std::vector<std::unique_ptr<Entity>>& entities,const std::vector<Entity*>& movableEntities) {
    for (size_t i = 0; i < movableEntities.size(); ++i) {
        Entity* entityA = movableEntities[i];
        if (!entityA->getIsAlive()) continue;
        for (size_t j = 0; j < entities.size(); ++j) {
            Entity* entityB = entities[j].get();

            if (entityA == entityB || !entityB->getIsAlive()) continue;

            if (std::find(movableEntities.begin(), movableEntities.begin() + i, entityB) != movableEntities.begin() + i)
                continue;

            if (checkCollision(entityA, entityB)) {
                handleCollision(entityA, entityB);
            }
        }
    }
}

void Collision::handleCollision(Entity* a, Entity* b) {

    string handlerKey = makeKey(a->getEntityTag(), b->getEntityTag());
    auto it = collisionHandlerMap.find(handlerKey);
    if (it != collisionHandlerMap.end()) {
        collisionHandlerMap[handlerKey](a, b);
    }
}

bool Collision::checkCollision(const Entity* a, const Entity* b) {
    return a->getBounds().intersects(b->getBounds());
}

string Collision::makeKey(const string& a, const string& b) {
    if (a >= b) {
        return a + "|" + b;
    }
    return b + "|" + a;
}

void Collision::addEntryToCollisionHandler(const string& a, const string& b, const std::function<void(Entity*, Entity*)>& handler) {

    collisionHandlerMap[makeKey(a, b)] = handler;

}
