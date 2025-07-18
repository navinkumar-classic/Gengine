//
// Created by navin on 7/15/25.
//
#pragma once

#include "../Entity.h"

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
        const sf::Vector2f& size,
        const sf::Color& color = sf::Color::Red);

    void update(float dt, Input& input) override;
    void render(sf::RenderWindow& window) override;
    void applyMovementToShape() override;

    sf::FloatRect getBounds() const override;

private:
    sf::RectangleShape shape;
    sf::Color color;
};

