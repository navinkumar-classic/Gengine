//
// Created by navin on 7/15/25.
//

#include "Collision.h"
#include <iostream>

#include "../../../Util/CollisionBehaviour.h"

void Collision::collisionManager(const std::vector<std::unique_ptr<Entity>>& entities,const std::vector<Entity*>& movableEntities) {
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

    string handlerKey = makeKey(a->getEntityTag(), b->getEntityTag());
    collisionHandlerMap[handlerKey](a, b);

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
