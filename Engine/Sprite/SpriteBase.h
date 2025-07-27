//
// Created by navin on 7/21/25.
//
#pragma once
#include <SFML/Graphics.hpp>

class SpriteBase {
public:
    virtual ~SpriteBase() = default;

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void setPosition(const sf::Vector2f& pos) = 0;
    virtual sf::FloatRect getBounds() const = 0;
};

