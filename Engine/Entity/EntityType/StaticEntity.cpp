//
// Created by navin on 7/15/25.
//

#include "StaticEntity.h"

StaticEntity::StaticEntity(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &color):
    Entity(0.0f, position, false, true), color(color){
    shape.setFillColor(color);
    shape.setPosition(position);
    setPreviousPosition(position);
    shape.setSize(size);
}

void StaticEntity::render(sf::RenderWindow& window) {
    window.draw(shape);
}

void StaticEntity::update(float dt, Input& input) {

}

sf::FloatRect StaticEntity::getBounds() const {
    return shape.getGlobalBounds();
}
