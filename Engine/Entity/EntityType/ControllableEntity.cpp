//
// Created by navin on 7/15/25.
//

#include "ControllableEntity.h"
#include <utility>
#include <iostream>

ControllableEntity::ControllableEntity(float speed, const sf::Vector2f &position, sf::Vector2u windowSize, const sf::Color &color, vector<string> actions, bool withinWindow):
Entity(speed, position, true, true), color(color), actionNames(std::move(actions)), withinWindow(withinWindow), windowSize(windowSize) {
    shape.setSize({32, 32});
    shape.setFillColor(color);
    shape.setPosition(position);
    setPreviousPosition(position);
}
void ControllableEntity::update(float dt, Input& input) {
    // Example input to action mapping
    for (const auto& action : actionNames) {
        if (input.isActionHeld(action)) {
            actionQueue.push_back(action);
        }
    }

    processActions(dt);

    if (withinWindow) {
        const sf::Vector2f size = shape.getSize();
        position.x = std::max(0.f, std::min(position.x, static_cast<float>(windowSize.x) - size.x));
        position.y = std::max(0.f, std::min(position.y, static_cast<float>(windowSize.y) - size.y));
    }

    shape.setPosition(position);
}

void ControllableEntity::render(sf::RenderWindow& window) {
    window.draw(shape);
}

void ControllableEntity::addAction(string& action) {
    actionQueue.push_back(action);
}

void ControllableEntity::clearActions() {
    actionQueue.clear();
}

void ControllableEntity::processActions(float dt) {
    sf::Vector2f newPos = getPosition();

    for (const auto& action : actionQueue) {
        if (action == "UP") {
            position.y -= speed * dt;
        } else if (action == "DOWN") {
            position.y += speed * dt;
        } else if (action == "LEFT") {
            position.x -= speed * dt;
        } else if (action == "RIGHT") {
            position.x += speed * dt;
        }
    }

    setPreviousPosition(newPos);
    actionQueue.clear();  // Clear after processing
}

sf::FloatRect ControllableEntity::getBounds() const {
    return shape.getGlobalBounds();
}
