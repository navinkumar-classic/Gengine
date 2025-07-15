//
// Created by navin on 7/15/25.
//

#pragma once

#include "../Entity.h"
#include <vector>

class ControllableEntity : public Entity {
public:
    ControllableEntity(float speed, const sf::Vector2f& position, sf::Vector2u windowSize, const sf::Color& color = sf::Color::Green, vector<string> actions = vector<string>(), bool withinWindow = true);

    void update(float dt, Input& input) override;
    void render(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;

    void addAction(string& action);
    void clearActions();

private:
    void processActions(float dt);

    std::vector<string> actionQueue;
    sf::RectangleShape shape;
    std::vector<string> actionNames;
    sf::Color color;
    bool withinWindow = true;
    sf::Vector2u windowSize;
};
