//
// Created by navin on 7/15/25.
//

#pragma once

#include <functional>
#include "../Entity.h"
#include <vector>

class ControllableEntity : public Entity {
public:
    ControllableEntity(float speed, const sf::Vector2f& position, sf::Vector2u windowSize,
        vector<std::pair<string, function<void(sf::Vector2f&, sf::Vector2f&, float, float, float, float, bool&, float, Input& input, string action)>>> actions,
        const sf::Color& color = sf::Color::Green );

    void update(float dt, Input& input) override;
    void render(sf::RenderWindow& window) override;
    void applyGravity(float dt) override;

    sf::FloatRect getBounds() const override;

    void addAction(string& action, function<void(sf::Vector2f&, sf::Vector2f&, float, float, float, float, bool&, float, Input& input, string action)>& func);
    void clearActions();

private:

    std::vector<std::pair<string, function<void(sf::Vector2f&, sf::Vector2f&, float, float, float, float, bool&, float, Input& input, string action)>>> action;
    sf::RectangleShape shape;
    sf::Color color;
    sf::Vector2u windowSize;
};
