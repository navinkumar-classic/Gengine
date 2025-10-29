//
// Created by navin on 10/22/25.
//

#pragma once
#include "../UIElement.h"
#include "../../GameState/GameState.h"
#include "../../Input/InputManager.h"

class TextUIElement: public UIElement {
    public:
        TextUIElement(
            const sf::Vector2f& position,
            int characterSize,
            const std::string& text,
            const sf::Font& font,
            const sf::Color& color,
            bool isDynamic,
            int pad_len,
            char pad_char);

        void update(float dt, const GameState& game_state, const InputManager& input) override;
        void render(sf::RenderWindow& window) override;

        void setPosition(const sf::Vector2f& position) override;
        void setCharacterSize(int size);
        void setText(const std::string& text);

        sf::FloatRect getBounds() const override;
        void setSize(const sf::Vector2f& size) override {};
        void setScale(const sf::Vector2f &scale) override {};
        bool getIsPressed() const override {return false;};

        std::string leftPad(const std::string& str, int width, char padChar);

    private:
        sf::Text m_text;
        int m_characterSize;
        std::string m_textString;

        // temp
        int pad_len;
        char pad_char;
};
