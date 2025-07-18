//
// Created by navin on 7/15/25.
//

#pragma once

#include <functional>
#include "../Entity.h"
#include <vector>

class ControllableEntity : public Entity {
public:
    ControllableEntity(
        bool isMovable,
        const sf::Vector2f& position,
        const sf::Vector2f& velocity,
        const sf::Vector2f& gravity,
        float maxSpeed,
        float terminalVelocity,
        float jumpStrength,
        float acceleration,
        float deacceleration,
        sf::Vector2u windowSize,
        vector<std::pair<string, function<void(ControllableEntity& entity, Input& input, string action, float dt)>>> actions,
        const sf::Color& color = sf::Color::Green
        );

    void update(float dt, Input& input) override;
    void render(sf::RenderWindow& window) override;
    void applyMovementToShape() override;

    sf::FloatRect getBounds() const override;

    void addAction(string& action, function<void(ControllableEntity& entity, Input& input, string action, float dt)>& func);
    void clearActions();

private:

    std::vector<std::pair<string, function<void(ControllableEntity& entity, Input& input, string action, float dt)>>> action;
    sf::RectangleShape shape;
    sf::Color color;
    sf::Vector2u windowSize;
};
