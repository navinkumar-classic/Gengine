//
// Created by navin on 7/14/25.
//

#include "Input.h"

void Input::bindAction(const string& action, sf::Keyboard::Key key) {
        actionBindings.insert({action, key});
        keyBindings.insert({key, action});

        keyHeld.insert({key, false});
        keyPressed.insert({key, false});
        keyReleased.insert({key, false});
}

sf::Keyboard::Key Input::getKeyForAction(const string& action) const {
        if (actionBindings.contains(action)) {
                return actionBindings.at(action);
        }

        return sf::Keyboard::Key::Unknown;
}

bool Input::isActionHeld(const string& action) const {
        if (actionBindings.contains(action)) {
                if (keyHeld.contains(actionBindings.at(action))) {
                        return keyHeld.at(actionBindings.at(action));
                }
        }
        return false;
}

bool Input::wasActionPressed(const string& action) const {
        if (actionBindings.contains(action)) {
                if (keyPressed.contains(actionBindings.at(action))) {
                        return keyPressed.at(actionBindings.at(action));
                }
        }
        return false;
}

bool Input::wasActionReleased(const string& action) const {
        if (actionBindings.contains(action)) {
                if (keyReleased.contains(actionBindings.at(action))) {
                        return keyReleased.at(actionBindings.at(action));
                }
        }
        return false;
}

void Input::reset() {
        for (auto & keyBinding : keyBindings) {
                keyPressed[keyBinding.first] = false;
                keyReleased[keyBinding.first] = false;
        }
}

void Input::updateEvent(const vector<sf::Event>& events) {
        for (auto & event : events) {
                if (event.type == sf::Event::KeyPressed) {
                        keyPressed[event.key.code] = true;
                        keyHeld[event.key.code] = true;
                }

                if (event.type == sf::Event::KeyReleased) {
                        keyReleased[event.key.code] = true;
                        keyHeld[event.key.code] = false;
                }
        }
}