//
// Created by navin on 7/15/25.
//

#include "AnimatedStaticEntity.h"
#include "../../Engine.h"

AnimatedStaticEntity::AnimatedStaticEntity(
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
        const sf::Vector2f& scale
        ):
        Entity(true, isMovable, position, velocity, gravity, maxSpeed, terminalVelocity, jumpStrength, acceleration, deacceleration, entityTag),
        Sprite(frame.x, frame.y, frameDuration, scale)
{
    setPreviousPosition(position);
    Sprite.setPosition(position);
}

AnimatedStaticEntity::AnimatedStaticEntity(
        const sf::Vector2f& position,
        const string& entityTag,
        const sf::Vector2i& frame,
        float frameDuration,
        const sf::Vector2f& scale,
        const string& spriteFile,
        int num_sprites
        ):
        Entity(true, false, position, sf::Vector2f(0.f,0.f), sf::Vector2f(0.f,0.f), 0.f, 0.f, 0.f, 0.f, 0.f, entityTag),
        Sprite(frame.x, frame.y, frameDuration, scale)
{
    setPreviousPosition(position);
    Sprite.addTexture("DEFAULT", spriteFile, num_sprites);
    Sprite.setPosition(position);
}

void AnimatedStaticEntity::render(sf::RenderWindow& window) {
    Sprite.draw(window);
}

void AnimatedStaticEntity::update(float dt, Engine& engine) {
    for (const auto& physicsFunction : physics) {
        physicsFunction(*this, engine.input, dt);
    }

    applyMovement(dt);
    applyMovementToShape();
    Sprite.update(dt);
}

void AnimatedStaticEntity::applyMovementToShape() {
    Sprite.setPosition(position);
}

sf::FloatRect AnimatedStaticEntity::getBounds() const {
    return Sprite.getBounds();
}