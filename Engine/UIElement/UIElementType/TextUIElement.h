//
// Created by navin on 10/22/25.
//

#pragma once
#include "../UIElement.h"
#include "../../GameState/GameState.h"

class TextUIElement: public UIElement {
    public:
        TextUIElement(
            const sf::Vector2f& position,
            int characterSize,
            const string& text,
            const sf::Font& font,
            const sf::Color& color,
            bool isDynamic);

        void update(float dt, const GameState& game_state) override;
        void render(sf::RenderWindow& window) override;

        void setPosition(const sf::Vector2f& position) override;
        void setCharacterSize(int size);
        void setText(const string& text);

        void setSize(const sf::Vector2f& size);
        void setScale(const sf::Vector2f& scale);

    private:
        sf::Text m_text;
        int m_characterSize;
        std::string m_textString;
};
