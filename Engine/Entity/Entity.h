//
// Created by navin on 7/15/25.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "../Input/Input.h"

class Entity {
public:
    Entity(float speed, const sf::Vector2f& position, bool isMovable, bool isSolid);
    virtual ~Entity() = default;

    virtual void update(float dt, Input& input) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual sf::FloatRect getBounds() const = 0;
    const bool isMovable;
    const bool isSolid;

    [[nodiscard]] sf::Vector2f getPosition() const;
    [[nodiscard]] sf::Vector2f getPreviousPosition() const;
    void setPosition(const sf::Vector2f& pos);
    void setPreviousPosition(const sf::Vector2f& pos);

protected:
    sf::Vector2f position;
    sf::Vector2f previousPosition;
    float speed = 0.0f;

};

