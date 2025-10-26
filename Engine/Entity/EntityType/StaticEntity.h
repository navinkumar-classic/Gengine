//
// Created by navin on 7/15/25.
//
#pragma once

#include "../Entity.h"
#include "../../Sprite/SpriteManager/TileManager.h"

class StaticEntity : public Entity {
public:
    StaticEntity(
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
        const std::unordered_map<int, std::string>& ref_texture);

    StaticEntity(
        const sf::Vector2f& position,
        const sf::Vector2f& tileSize,
        const std::vector<std::vector<int>>& tilemat,
        const string& entityTag,
        const std::unordered_map<int, std::string>& ref_texture);

    void update(float dt, InputManager& input) override;
    void render(sf::RenderWindow& window) override;
    void applyMovementToShape() override;

    sf::FloatRect getBounds() const override;
    TileMap tileMap;
private:
    const sf::Vector2f tileSize;

};

