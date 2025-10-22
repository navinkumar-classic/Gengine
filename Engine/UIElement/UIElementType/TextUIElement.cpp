//
// Created by navin on 10/22/25.
//

#include "TextUIElement.h"

#include <iostream>
#include <stack>
TextUIElement::TextUIElement(
    const sf::Vector2f &position,
    const int characterSize,
    const string &text,
    const sf::Font &font,
    const sf::Color &color,
    bool isDynamic):
    UIElement(position, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), isDynamic),
    m_characterSize(characterSize), m_textString(text){
    m_text.setFont(font);
    m_text.setString(text);
    m_text.setCharacterSize(characterSize);
    m_text.setFillColor(color);
    m_text.setPosition(position);
}

void TextUIElement::update(float dt, const GameState& game_state){
    std::string output;
    std::stack<size_t> openTags;

    for (size_t i = 0; i < m_textString.size(); ++i) {
        char c = m_textString[i];

        if (c == '<') {
            openTags.push(output.size());
        }
        else if (c == '>' && !openTags.empty()) {
            size_t openPos = openTags.top();
            openTags.pop();

            std::string key = output.substr(openPos);
            output.erase(openPos);
            output += game_state.getString(key);
        }
        else {
            output += c;
        }
    }

    m_text.setString(output);

}

void TextUIElement::render(sf::RenderWindow& window) {
    window.draw(m_text);
}

void TextUIElement::setPosition(const sf::Vector2f& inPosition) {
    position = inPosition;
    m_text.setPosition(inPosition);
}

void TextUIElement::setText(const string& text) {
    m_textString = text;
    m_text.setString(text);
}

void TextUIElement::setCharacterSize(int characterSize) {
    m_characterSize = characterSize;
    m_text.setCharacterSize(characterSize);
}






//
void TextUIElement::setSize(const sf::Vector2f& size) {

}
void TextUIElement::setScale(const sf::Vector2f& scale) {

}
