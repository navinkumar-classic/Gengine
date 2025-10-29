//
// Created by navin on 7/15/25.
//

#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include "../Input/InputManager.h"
class Engine;

class Entity {
public:
    Entity(
        bool isAnimated,
        bool isMovable,
        const sf::Vector2f& position,
        const sf::Vector2f& velocity,
        const sf::Vector2f& gravity,
        float maxSpeed,
        float terminalVelocity,
        float jumpStrength,
        float acceleration,
        float deacceleration,
        const string& entityTag
        );
    virtual ~Entity() = default;

    virtual void update(float dt, Engine& engine) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    [[nodiscard]] virtual sf::FloatRect getBounds() const = 0;
    virtual void applyMovementToShape() = 0;

    [[nodiscard]] sf::Vector2f getPosition() const;
    [[nodiscard]] sf::Vector2f getPreviousPosition() const;
    [[nodiscard]] sf::Vector2f getVelocity() const;
    [[nodiscard]] sf::Vector2f getGravity() const;
    [[nodiscard]] float getMaxSpeed() const;
    [[nodiscard]] float getTerminalVelocity() const;
    [[nodiscard]] float getJumpStrength() const;
    [[nodiscard]] float getAcceleration() const;
    [[nodiscard]] float getDeacceleration() const;
    [[nodiscard]] bool getOnGround() const;
    [[nodiscard]] bool getJump() const;
    [[nodiscard]] string getEntityTag() const;
    [[nodiscard]] bool getIsAlive() const;

    void setPosition(const sf::Vector2f& pos);
    void setPreviousPosition(const sf::Vector2f& pos);
    void setVerticalVelocity(float velocity);
    void setHorizontalVelocity(float velocity);
    void setGravity(const sf::Vector2f& gravity);
    void setMaxSpeed(float maxSpeed);
    void setTerminalVelocity(float terminalVelocity);
    void setJumpStrength(float jumpStrength);
    void setAcceleration(float acceleration);
    void setDeacceleration(float deacceleration);
    void setOnGround(bool onGround);
    void setJump(bool jump);
    void setIsAlive(bool isAlive);

    void applyMovement(float dt);

    void addPhysics(function<void(Entity&, InputManager&, float)> function);

    const bool isMovable;
    const bool isAnimated;
    sf::Vector2f position;

protected:
    vector<function<void(Entity&, InputManager&, float)>> physics;
    sf::Vector2f previousPosition;

    sf::Vector2f velocity;
    sf::Vector2f gravity;

    float maxSpeed;
    float terminalVelocity;
    float jumpStrength;
    float acceleration;
    float deacceleration;

    bool onGround = false;
    bool jump = false;
    string entityTag;
    bool isAlive = true;
};

