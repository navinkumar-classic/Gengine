//
// Created by navin on 7/15/25.
//
#pragma once

#include "../Entity.h"

class StaticEntity : public Entity {
public:
    StaticEntity(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color = sf::Color::Red);

    void update(float dt, Input& input) override;
    void render(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;

private:
    sf::RectangleShape shape;
    sf::Color color;
};

