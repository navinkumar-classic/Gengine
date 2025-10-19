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
    // Current global bounds (SFML accounts for scale/flip here)
    sf::FloatRect aBounds = a->getBounds();
    sf::FloatRect bBounds = b->getBounds();

    // Positions & velocity
    sf::Vector2f aPrev = a->getPreviousPosition();
    sf::Vector2f aCurr = a->getPosition();
    sf::Vector2f aVel  = a->getVelocity();

    const float epsilon = 1.0f;

    // Width/height from current bounds
    float aw = aBounds.width;
    float ah = aBounds.height;

    // ---- ADD THIS ----
    // Narrow the X hitbox to allow visual overlap.
    // Example: sprite is 64x64, but real body is 48px wide.
    const float hitboxNarrowing = 40.0f;   // total reduction (8px each side)
    float effectiveWidth = aw - hitboxNarrowing;
    float halfWidth = effectiveWidth / 2.0f;
    // ------------------

    // Edges for current position (origin.x is centered, origin.y is top)
    float aCurrLeft   = aCurr.x - halfWidth;
    float aCurrRight  = aCurr.x + halfWidth;
    float aCurrTop    = aCurr.y;
    float aCurrBottom = aCurr.y + ah;

    // Edges for previous position (use same narrowed size)
    float aPrevLeft   = aPrev.x - halfWidth;
    float aPrevRight  = aPrev.x + halfWidth;
    float aPrevTop    = aPrev.y;
    float aPrevBottom = aPrev.y + ah;

    // Static block edges
    float bLeft   = bBounds.left;
    float bRight  = bBounds.left + bBounds.width;
    float bTop    = bBounds.top;
    float bBottom = bBounds.top + bBounds.height;

    // Overlaps (using current position)
    bool overlapsX = (aCurrRight > bLeft) && (aCurrLeft < bRight);
    bool overlapsY = (aCurrBottom > bTop) && (aCurrTop < bBottom);

    // --- VERTICAL COLLISIONS ---
    bool isFalling  = aVel.y >= 0;
    bool isMovingUp = aVel.y < 0;

    bool wasAbove = (aPrevBottom <= bTop + epsilon);
    bool nowOverlapsTop = (aCurrBottom > bTop);

    if (isFalling && wasAbove && nowOverlapsTop && overlapsX) {
        a->setOnGround(true);
        a->setJump(false);
        a->setVerticalVelocity(0);
        a->setPosition({ aCurr.x, bTop - ah });
        return;
    }

    bool wasBelow = (aPrevTop >= bBottom - epsilon);
    bool nowHitsCeiling = (aCurrTop < bBottom);

    if (isMovingUp && wasBelow && nowHitsCeiling && overlapsX) {
        a->setVerticalVelocity(0);
        a->setPosition({ aCurr.x, bBottom });
        return;
    }

    // --- HORIZONTAL COLLISIONS ---
    if ((aPrevRight <= bLeft + epsilon) && (aCurrRight > bLeft) && overlapsY) {
        a->setPosition({ bLeft - halfWidth, aCurr.y });
        a->setHorizontalVelocity(0);
        return;
    }

    if ((aPrevLeft >= bRight - epsilon) && (aCurrLeft < bRight) && overlapsY) {
        a->setPosition({ bRight + halfWidth, aCurr.y });
        a->setHorizontalVelocity(0);
        return;
    }
}

