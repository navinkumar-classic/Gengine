//
// Created by navin on 7/14/25.
//

#pragma once

#include <SFML/Window.hpp>
#include <unordered_map>
#include <string>

using namespace std;

class Input {
public:
    void updateEvent(const vector<sf::Event>& events);

    void reset();

    bool isActionHeld(const string& action) const;
    bool wasActionPressed(const string& action) const;
    bool wasActionReleased(const string& action) const;

    void bindAction(const string& action, sf::Keyboard::Key key);
    sf::Keyboard::Key getKeyForAction(const string& action) const;

private:
    unordered_map<sf::Keyboard::Key, bool> keyHeld;
    unordered_map<sf::Keyboard::Key, bool> keyPressed;
    unordered_map<sf::Keyboard::Key, bool> keyReleased;

    unordered_map<string, sf::Keyboard::Key> actionBindings;
    unordered_map<sf::Keyboard::Key, string> keyBindings;
};

