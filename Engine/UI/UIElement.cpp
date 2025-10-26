//
// Created by navin on 10/22/25.
//

#include "UIElement.h"

UIElement::UIElement(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const sf::Vector2f& scale,
    bool isDynamic
    ):
    position(position), size(size), scale(scale), isVisible(true), isDynamic(isDynamic) {}

sf::Vector2f UIElement::getPosition() const {
    return position;
}

sf::Vector2f UIElement::getSize() const {
    return size;
}

sf::Vector2f UIElement::getScale() const {
    return scale;
}

bool UIElement::getIsVisible() const {
    return isVisible;
}

bool UIElement::getIsDynamic() const {
    return isDynamic;
}

void UIElement::setVisible(bool inpVisible) {
    isVisible = inpVisible;
}

void UIElement::setDynamic(bool inpDynamic) {
    isDynamic = inpDynamic;
}