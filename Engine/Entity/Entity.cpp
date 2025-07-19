//
// Created by navin on 7/15/25.
//

#include "Entity.h"

#include <utility>

Entity::Entity(
       bool isMovable,
       const sf::Vector2f& position,
       const sf::Vector2f& velocity,
       const sf::Vector2f& gravity,
       float maxSpeed,
       float terminalVelocity,
       float jumpStrength,
       float acceleration,
       float deacceleration
       ):
    isMovable(isMovable),
    position(position),
    previousPosition(position),
    velocity(velocity),
    gravity(gravity),
    maxSpeed(maxSpeed),
    terminalVelocity(terminalVelocity),
    jumpStrength(jumpStrength),
    acceleration(acceleration),
    deacceleration(deacceleration){
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

sf::Vector2f Entity::getGravity() const {
    return gravity;
}

float Entity::getMaxSpeed() const {
    return maxSpeed;
}

float Entity::getTerminalVelocity() const {
    return terminalVelocity;
}

float Entity::getJumpStrength() const {
    return jumpStrength;
}

float Entity::getAcceleration() const {
    return acceleration;
}

float Entity::getDeacceleration() const {
    return deacceleration;
}

bool Entity::getOnGround() const {
    return onGround;
}

bool Entity::getJump() const {
    return jump;
}

// setters
void Entity::setPosition(const sf::Vector2f& pos) {
    position = pos;
}

void Entity::setPreviousPosition(const sf::Vector2f& pos) {
    previousPosition = pos;
}

void Entity::setVerticalVelocity(float velocity) {
    Entity::velocity.y = velocity;
}

void Entity::setHorizontalVelocity(float velocity) {
    Entity::velocity.x = velocity;
}

void Entity::setGravity(const sf::Vector2f& gravity) {
    Entity::gravity = gravity;
}

void Entity::setMaxSpeed(float maxSpeed) {
    Entity::maxSpeed = maxSpeed;
}

void Entity::setTerminalVelocity(float terminalVelocity) {
    Entity::terminalVelocity = terminalVelocity;
}

void Entity::setJumpStrength(float jumpStrength) {
    Entity::jumpStrength = jumpStrength;
}

void Entity::setAcceleration(float acceleration) {
    Entity::acceleration = acceleration;
}

void Entity::setDeacceleration(float deacceleration) {
    Entity::deacceleration = deacceleration;
}

void Entity::setOnGround(bool onGround) {
    Entity::onGround = onGround;
}

void Entity::setJump(bool jump) {
    Entity::jump = jump;
}

void Entity::applyMovement(float dt) {
    position += velocity * dt;
}

void Entity::addPhysics(function<void(Entity& entity, Input& input, float dt)> function) {
    physics.emplace_back(function);
}


