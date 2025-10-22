//
// Created by navin on 10/22/25.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "../Input/Input.h"
#include "../GameState/GameState.h"

class UIElement {
    public:
        UIElement(
            const sf::Vector2f& position,
            const sf::Vector2f& size,
            const sf::Vector2f& scale,
            bool isDynamic);
        virtual ~UIElement() = default;

        virtual void update(float dt, const GameState& game_state) = 0;
        virtual void render(sf::RenderWindow& window) = 0;

        [[nodiscard]] bool getIsVisible() const;
        [[nodiscard]] sf::Vector2f getPosition() const;
        [[nodiscard]] sf::Vector2f getSize() const;
        [[nodiscard]] sf::Vector2f getScale() const;
        [[nodiscard]] bool getIsDynamic() const;

        virtual void setPosition(const sf::Vector2f& position) = 0;
        virtual void setSize(const sf::Vector2f& size) = 0;
        virtual void setScale(const sf::Vector2f& scale) = 0;

        void setVisible(bool visible);
        void setDynamic(bool isDynamic);
    protected:
        sf::Vector2f position;
        sf::Vector2f size;
        sf::Vector2f scale;

        bool isVisible;
        bool isDynamic;
};
