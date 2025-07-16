//
// Created by navin on 7/16/25.
//

#include "CollisionBehaviour.h"
#include <iostream>

void CollisionBehaviour::ControllableToStaticCollision(Entity *a, Entity *b) {
    sf::FloatRect aBounds = a->getBounds();
    sf::FloatRect bBounds = b->getBounds();

    sf::Vector2f aPrev = a->getPreviousPosition();
    sf::Vector2f bPrev = b->getPreviousPosition();
    sf::Vector2f aCurr = a->getPosition();

    bool groundCollision = aPrev.y + aBounds.height <= bBounds.top + 1 && a->getVelocity().y >= 0;

    bool noSidewayCollision = bBounds.left < aCurr.x && aCurr.x + 5  < bBounds.left + bBounds.width;

    bool ceilingCollision = bPrev.y + bBounds.height <= aBounds.top + 1 && (noSidewayCollision);

    if (groundCollision) {
        a->setOnGround(true);
        a->setVerticalVelocity(0);
        a->setPosition({aCurr.x, aPrev.y});
    }
    else if (ceilingCollision) {
        a->setPosition({aCurr.x, aPrev.y});
        a->setVerticalVelocity(-1.0f * a->getVelocity().y);
        std::cout << "Vertical collision (ceiling)\n";
    }
    else {
        a->setPosition({aPrev.x, aCurr.y});
    }
}

void CollisionBehaviour::ControllableToControllableCollision(Entity *a, Entity *b) {
    a->setPosition(a->getPreviousPosition());
    b->setPosition(b->getPreviousPosition());
}


