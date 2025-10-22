//
// Created by navin on 7/15/25.
//
#pragma once

#include "../Entity.h"
#include "../../Sprite/SpriteManager/AnimatedSprite.h"

class AnimatedStaticEntity : public Entity {
public:
    AnimatedStaticEntity(
        bool isMovable,
        const sf::Vector2f& position,
        const sf::Vector2f& velocity,
        const sf::Vector2f& gravity,
        float maxSpeed,
        float terminalVelocity,
        float jumpStrength,
        float acceleration,
        float deacceleration,
        const string& entityTag,
        const sf::Vector2i& frame,
        float frameDuration,
        const sf::Vector2f& scale);

    AnimatedStaticEntity(
        const sf::Vector2f& position,
        const string& entityTag,
        const sf::Vector2i& frame,
        float frameDuration,
        const sf::Vector2f& scale,
        const string& spriteFile,
        int num_sprites);

    void update(float dt, Input& input) override;
    void render(sf::RenderWindow& window) override;
    void applyMovementToShape() override;

    sf::FloatRect getBounds() const override;
    AnimatedSprite Sprite;

};

