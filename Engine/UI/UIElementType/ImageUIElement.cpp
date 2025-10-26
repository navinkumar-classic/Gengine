//
// Created by navin on 10/24/25.
//

#include "ImageUIElement.h"

#include <iostream>

ImageUIElement::ImageUIElement(
    const sf::Vector2f &position,
    const sf::Vector2f &size,
    const sf::Vector2f &scale,
    bool isDynamic,
    const std::string &texturePath):
    UIElement(position, size, scale, isDynamic){
    setTexture(texturePath);
    sprite.setPosition(position);
    sprite.setScale(scale);
}

void ImageUIElement::update(float dt, const GameState& game_state, const InputManager& input) {
    isPressed = false;
    if (input.wasMousePressed(sf::Mouse::Left)) {
        if (sprite.getGlobalBounds().contains(input.getMousePosition())) {
            isPressed = true;
        }
    }
}

void ImageUIElement::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void ImageUIElement::setPosition(const sf::Vector2f &inpPosition) {
    sprite.setPosition(inpPosition);
    position = inpPosition;
}

void ImageUIElement::setScale(const sf::Vector2f &inpScale) {
    sprite.setScale(inpScale);
    scale = inpScale;
}

void ImageUIElement::setSize(const sf::Vector2f &inpSize) {
    sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y)));
    size = inpSize;
}

void ImageUIElement::setTexture(const std::string& texturePath) {
    if (!texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Failed to load texture: " + texturePath);
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(size.x), static_cast<int>(size.y)));

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

sf::FloatRect ImageUIElement::getBounds() const {
    return sprite.getGlobalBounds();
}

bool ImageUIElement::getIsPressed() const {
    return isPressed;
}


