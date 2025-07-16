//
// Created by navin on 7/15/25.
//

#include "Entity.h"

Entity::Entity(float maxSpeed, const sf::Vector2f& position, bool isMovable, bool isSolid, bool isGravityEnabled) :
    maxSpeed(maxSpeed), position(position), isMovable(isMovable), isSolid(isSolid), previousPosition(position), gravityEnabled(isGravityEnabled){
}

//getters
sf::Vector2f Entity::getPosition() const {
        return position;
}

sf::Vector2f Entity::getPreviousPosition() const {
    return previousPosition;
}

sf::Vector2f Entity::getVelocity() const {
    return velocity;
}

// setters
void Entity::setPosition(const sf::Vector2f& pos) {
    position = pos;
}

void Entity::setPreviousPosition(const sf::Vector2f& pos) {
    previousPosition = pos;
}

void Entity::setGravityEnabled(bool enabled) {
    gravityEnabled = enabled;
}

void Entity::setGravity(const sf::Vector2f& gravity) {
    Entity::gravity = gravity;
}

void Entity::setVerticalVelocity(float velocity) {
    Entity::velocity.y = velocity;
}

void Entity::setOnGround(bool onGround) {
    Entity::onGround = onGround;
}


