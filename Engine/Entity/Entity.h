//
// Created by navin on 7/15/25.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "../Input/Input.h"

class Entity {
public:
    Entity(float speed, const sf::Vector2f& position, bool isMovable, bool isSolid, bool isGravityEnabled);
    virtual ~Entity() = default;

    virtual void update(float dt, Input& input) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void applyGravity(float dt) = 0;

    const bool isMovable;
    const bool isSolid;

    [[nodiscard]] sf::Vector2f getPosition() const;
    [[nodiscard]] sf::Vector2f getPreviousPosition() const;
    [[nodiscard]] virtual sf::FloatRect getBounds() const = 0;
    [[nodiscard]] sf::Vector2f getVelocity() const;

    void setPosition(const sf::Vector2f& pos);
    void setPreviousPosition(const sf::Vector2f& pos);
    void setGravityEnabled(bool enabled);
    void setGravity(const sf::Vector2f& gravity);
    void setVerticalVelocity(float velocity);
    void setOnGround(bool onGround);

protected:
    sf::Vector2f position;
    sf::Vector2f previousPosition;

    sf::Vector2f velocity = {0.0f, 0.0f};
    sf::Vector2f gravity = {0.0f, 500.0f};

    float maxSpeed = 0.0f;
    float jumpStrength = -500.f;
    float acceleration = 400.0f;
    float deacceleration = 700.0f;

    bool gravityEnabled = false;
    bool onGround = false;
};

