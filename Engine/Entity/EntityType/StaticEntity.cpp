//
// Created by navin on 7/15/25.
//

#include "StaticEntity.h"

StaticEntity::StaticEntity(
        bool isMovable,
        const sf::Vector2f& position,
        const sf::Vector2f& velocity,
        const sf::Vector2f& gravity,
        float maxSpeed,
        float terminalVelocity,
        float jumpStrength,
        float acceleration,
        float deacceleration,
        const sf::Vector2f& tileSize,
        const std::vector<std::vector<int>>& tilemat,
        const string& entityTag,
        const std::unordered_map<int, std::string>& ref_texture
        ):
        Entity(false, isMovable, position, velocity, gravity, maxSpeed, terminalVelocity, jumpStrength, acceleration, deacceleration, entityTag),
        tileMap(tileSize.x, tileSize.y, ref_texture)
{
    const float new_x = position.x + tilemat[0].size()*tileSize.x/2.f;
    const float new_y = position.y + tilemat.size()*tileSize.y/2.f;

    const sf::Vector2f adjPosition = sf::Vector2f(new_x,new_y);
    setPreviousPosition(adjPosition);
    tileMap.setPosition(adjPosition);

    tileMap.setMatrix(tilemat);
}

StaticEntity::StaticEntity(
        const sf::Vector2f& position,
        const sf::Vector2f& tileSize,
        const std::vector<std::vector<int>>& tilemat,
        const string& entityTag,
        const std::unordered_map<int, std::string>& ref_texture
        ):
        Entity(false, false, position, sf::Vector2f(0.f,0.f), sf::Vector2f(0.f,0.f), 0.f, 0.f, 0.f, 0.f, 0.f, entityTag),
        tileMap(tileSize.x, tileSize.y, ref_texture)
{
    const float new_x = position.x + tilemat[0].size()*tileSize.x/2.f;
    const float new_y = position.y + tilemat.size()*tileSize.y/2.f;

    const sf::Vector2f adjPosition = sf::Vector2f(new_x,new_y);
    setPreviousPosition(adjPosition);
    tileMap.setPosition(adjPosition);

    tileMap.setMatrix(tilemat);
}

void StaticEntity::render(sf::RenderWindow& window) {
    tileMap.draw(window);
}

void StaticEntity::update(float dt, InputManager& input) {
    for (const auto& physicsFunction : physics) {
        physicsFunction(*this, input, dt);
    }

    applyMovement(dt);
    applyMovementToShape();
}

void StaticEntity::applyMovementToShape() {
    tileMap.setPosition(position);
}

sf::FloatRect StaticEntity::getBounds() const {
    return tileMap.getBounds();
}