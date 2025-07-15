//
// Created by navin on 7/15/25.
//

#include "Entity.h"

Entity::Entity(float speed, const sf::Vector2f& position, bool isMovable, bool isSolid) :
    speed(speed), position(position), isMovable(isMovable), isSolid(isSolid), previousPosition(position){
}

sf::Vector2f Entity::getPosition() const {
        return position;
}

sf::Vector2f Entity::getPreviousPosition() const {
    return previousPosition;
}

void Entity::setPosition(const sf::Vector2f& pos) {
    position = pos;
}

void Entity::setPreviousPosition(const sf::Vector2f& pos) {
    previousPosition = pos;
}
