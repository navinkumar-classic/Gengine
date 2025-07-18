//
// Created by navin on 7/14/25.
//

#include "Input.h"

#include <iostream>

void Input::bindAction(const string& action, sf::Keyboard::Key key) {
        actionBindings.insert({action, key});
        keyBindings.insert({key, action});

        keyHeld.insert({key, false});
        keyPressed.insert({key, false});
        keyReleased.insert({key, false});
        keyHoldDuration.insert({key, 0.0f});
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

float Input::getHoldDuration(const string& action) const {
        if (actionBindings.contains(action)) {
                return keyHoldDuration.at(actionBindings.at(action));
        }
        return 0.0f;
}

void Input::reset() {
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
}

void Input::updateEvent(const vector<sf::Event>& events, float dt) {
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
        }
}