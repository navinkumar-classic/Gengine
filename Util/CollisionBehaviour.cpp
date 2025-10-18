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

    // Edges for current position (origin.x is centered, origin.y is top)
    float aCurrLeft   = aCurr.x - aw / 2.0f;
    float aCurrRight  = aCurr.x + aw / 2.0f;
    float aCurrTop    = aCurr.y;
    float aCurrBottom = aCurr.y + ah;

    // Edges for previous position (compute using same size)
    float aPrevLeft   = aPrev.x - aw / 2.0f;
    float aPrevRight  = aPrev.x + aw / 2.0f;
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

    // Ground (came from above)
    bool wasAbove = (aPrevBottom <= bTop + epsilon);
    bool nowOverlapsTop = (aCurrBottom > bTop);

    if (isFalling && wasAbove && nowOverlapsTop && overlapsX) {
        a->setOnGround(true);
        a->setJump(false);
        a->setVerticalVelocity(0);
        // Snap using center-x, top-y convention
        a->setPosition({ aCurr.x, bTop - ah });
        return;
    }

    // Ceiling (came from below)
    bool wasBelow = (aPrevTop >= bBottom - epsilon);
    bool nowHitsCeiling = (aCurrTop < bBottom);

    if (isMovingUp && wasBelow && nowHitsCeiling && overlapsX) {
        a->setVerticalVelocity(0);
        a->setPosition({ aCurr.x, bBottom });
        return;
    }

    // --- HORIZONTAL COLLISIONS (use crossing detection) ---
    // Collided from left: previously right edge was <= block left, now right edge > block left
    if ((aPrevRight <= bLeft + epsilon) && (aCurrRight > bLeft) && overlapsY) {
        // Snap so entity's right edge sits flush with block left edge
        a->setPosition({ bLeft - aw / 2.0f, aCurr.y });
        a->setHorizontalVelocity(0);
        return;
    }

    // Collided from right: previously left edge was >= block right, now left edge < block right
    if ((aPrevLeft >= bRight - epsilon) && (aCurrLeft < bRight) && overlapsY) {
        // Snap so entity's left edge sits flush with block right edge
        a->setPosition({ bRight + aw / 2.0f, aCurr.y });
        a->setHorizontalVelocity(0);
        return;
    }
}
