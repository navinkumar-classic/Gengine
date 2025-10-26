//
// Created by navin on 10/24/25.
//

#pragma once
#include "../UIElement.h"
#include "../../Input/InputManager.h"

class ImageUIElement: public UIElement {
    public:
        ImageUIElement(
            const sf::Vector2f& position,
            const sf::Vector2f& size,
            const sf::Vector2f& scale,
            bool isDynamic,
            const std::string& texturePath);

        void update(float dt, const GameState& game_state, const InputManager& input) override;
        void render(sf::RenderWindow& window) override;

        void setPosition(const sf::Vector2f &position) override;
        void setSize(const sf::Vector2f &size) override;
        void setScale(const sf::Vector2f &scale) override;
        void setTexture(const std::string& texturePath);

        sf::FloatRect getBounds() const override;
        bool getIsPressed() const override;

    private:
        sf::Sprite sprite;
        sf::Texture texture;

        bool isPressed = false;
};
