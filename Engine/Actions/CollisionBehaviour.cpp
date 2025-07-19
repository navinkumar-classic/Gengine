//
// Created by navin on 7/16/25.
//

#include "CollisionBehaviour.h"
#include <iostream>

/*
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
        a->setJump(false);
        a->setVerticalVelocity(0);
        a->setPosition({aCurr.x, aPrev.y});
    }
    else if (ceilingCollision) {
        a->setPosition({aCurr.x, aPrev.y});
        a->setVerticalVelocity(-1.0f * a->getVelocity().y);
    }
    else {
        a->setPosition({aPrev.x, aCurr.y});
    }
}
*/
void CollisionBehaviour::ControllableToControllableCollision(Entity *a, Entity *b) {
    a->setPosition(a->getPreviousPosition());
    b->setPosition(b->getPreviousPosition());
}

void CollisionBehaviour::ControllableToStaticCollision(Entity *a, Entity *b) {
    sf::FloatRect aBounds = a->getBounds();
    sf::FloatRect bBounds = b->getBounds();

    sf::Vector2f aPrev = a->getPreviousPosition();
    sf::Vector2f aCurr = a->getPosition();
    sf::Vector2f aVel  = a->getVelocity();

    const float epsilon = 1.0f; // small margin for float comparisons

    // Vertical Collision: Ground
    bool isFalling = aVel.y >= 0;
    bool wasAbove = aPrev.y + aBounds.height <= bBounds.top + epsilon;
    bool nowOverlapsY = aCurr.y + aBounds.height > bBounds.top;
    bool overlapsX = aCurr.x + aBounds.width > bBounds.left &&
                     aCurr.x < bBounds.left + bBounds.width;

    if (isFalling && wasAbove && nowOverlapsY && overlapsX) {
        a->setOnGround(true);
        a->setJump(false);
        a->setVerticalVelocity(0);
        // Snap to top of static block
        a->setPosition({aCurr.x, bBounds.top - aBounds.height});
        return;
    }

    // Vertical Collision: Ceiling
    bool isMovingUp = aVel.y < 0;
    bool wasBelow = aPrev.y >= bBounds.top + bBounds.height - epsilon;
    bool nowHitsCeiling = aCurr.y < bBounds.top + bBounds.height;
    if (isMovingUp && wasBelow && nowHitsCeiling && overlapsX) {
        a->setVerticalVelocity(0);
        // Snap below the ceiling
        a->setPosition({aCurr.x, bBounds.top + bBounds.height});
        return;
    }

    // Horizontal Collision: From Left or Right
    bool wasLeft = aPrev.x + aBounds.width <= bBounds.left + epsilon;
    bool wasRight = aPrev.x >= bBounds.left + bBounds.width - epsilon;
    bool overlapsY = aCurr.y + aBounds.height > bBounds.top &&
                     aCurr.y < bBounds.top + bBounds.height;

    if (wasLeft && aCurr.x + aBounds.width > bBounds.left && overlapsY) {
        // Collided from left
        a->setPosition({bBounds.left - aBounds.width, aCurr.y});
        a->setHorizontalVelocity(0);
        return;
    }
    if (wasRight && aCurr.x < bBounds.left + bBounds.width && overlapsY) {
        // Collided from right
        a->setPosition({bBounds.left + bBounds.width, aCurr.y});
        a->setHorizontalVelocity(0);
    }
}



