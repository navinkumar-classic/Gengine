//
// Created by navin on 7/14/25.
//

#include "InputManager.h"

#include <iostream>
#include <ranges>
#include <SFML/Graphics/RenderWindow.hpp>

void InputManager::bindAction(const string& action, sf::Keyboard::Key key) {
        actionBindings.insert({action, key});
        keyBindings.insert({key, action});

        keyHeld.insert({key, false});
        keyPressed.insert({key, false});
        keyReleased.insert({key, false});
        keyHoldDuration.insert({key, 0.0f});
}

sf::Keyboard::Key InputManager::getKeyForAction(const string& action) const {
        if (actionBindings.contains(action)) {
                return actionBindings.at(action);
        }

        return sf::Keyboard::Key::Unknown;
}

bool InputManager::isActionHeld(const string& action) const {
        if (actionBindings.contains(action)) {
                if (keyHeld.contains(actionBindings.at(action))) {
                        return keyHeld.at(actionBindings.at(action));
                }
        }
        return false;
}

bool InputManager::wasActionPressed(const string& action) const {
        if (actionBindings.contains(action)) {
                if (keyPressed.contains(actionBindings.at(action))) {
                        return keyPressed.at(actionBindings.at(action));
                }
        }
        return false;
}

bool InputManager::wasActionReleased(const string& action) const {
        if (actionBindings.contains(action)) {
                if (keyReleased.contains(actionBindings.at(action))) {
                        return keyReleased.at(actionBindings.at(action));
                }
        }
        return false;
}

float InputManager::getHoldDuration(const string& action) const {
        if (actionBindings.contains(action)) {
                return keyHoldDuration.at(actionBindings.at(action));
        }
        return 0.0f;
}

bool InputManager::isMouseHeld(sf::Mouse::Button button) const {
        if (mouseHeld.contains(button)) {
                return mouseHeld.at(button);
        }
        return false;
}

bool InputManager::wasMousePressed(sf::Mouse::Button button) const {
        if (mousePressed.contains(button)) {
                return mousePressed.at(button);
        }
        return false;
}

bool InputManager::wasMouseReleased(sf::Mouse::Button button) const {
        if (mouseReleased.contains(button)) {
                return mouseReleased.at(button);
        }
        return false;
}

sf::Vector2<float> InputManager::getMousePosition() const {
        return static_cast<sf::Vector2f>(mousePosition);
}

void InputManager::reset() {
        for (auto & key : keyReleased) {
                if ( key.second) {
                        keyHoldDuration[key.first] = 0.0f;
                        keyReleased[key.first] = false;
                }
        }

        for (auto & key : keyBindings) {
                keyPressed[key.first] = false;
                keyReleased[key.first] = false;
        }

        for (auto &state: mousePressed | views::values)
                state = false;

        for (auto &state: mouseReleased | views::values)
                state = false;
}

void InputManager::updateEvent(const vector<sf::Event>& events, const sf::RenderWindow& window, const float dt) {
        for (auto& key : keyHeld) {
                if (key.second) {
                        keyHoldDuration[key.first] += dt;
                }
        }
        for (auto & event : events) {
                if (event.type == sf::Event::KeyPressed && keyHeld[event.key.code] == false) {
                        keyPressed[event.key.code] = true;
                        keyHeld[event.key.code] = true;
                }

                if (event.type == sf::Event::KeyReleased && keyHeld[event.key.code] == true) {
                        keyHeld[event.key.code] = false;
                        keyReleased[event.key.code] = true;
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        mousePressed[event.mouseButton.button] = true;
                        mouseHeld[event.mouseButton.button] = true;
                        mousePosition = mousePos;
                }

                if (event.type == sf::Event::MouseButtonReleased) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        mouseHeld[event.mouseButton.button] = false;
                        mouseReleased[event.mouseButton.button] = true;
                        mousePosition = mousePos;
                }

                if (event.type == sf::Event::MouseMoved) {
                        mousePosition = { event.mouseMove.x, event.mouseMove.y };
                }
        }
}