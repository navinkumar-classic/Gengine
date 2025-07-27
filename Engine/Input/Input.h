//
// Created by navin on 7/14/25.
//

#pragma once

#include <SFML/Window.hpp>
#include <unordered_map>
#include <string>

using namespace std;

/**
 * @brief Handles user input and maps key events to high-level actions.
 *
 * The Input class maintains state for keyboard input, such as whether
 * a key is pressed, released, or held. It also allows mapping strings
 * (actions) to specific keys, enabling flexible control schemes.
 */
class Input {
public:
    /**
     * @brief Updates input state based on a list of SFML events.
     *
     * This method should be called every frame to track input state changes,
     * such as presses, releases, and duration for held keys.
     *
     * @param events A list of SFML events polled from the window.
     * @param dt Delta time in seconds since the last frame.
     */
    void updateEvent(const vector<sf::Event>& events, float dt);

    /**
     * @brief Resets all key state (pressed/released/held) for a new frame.
     *
     * Should be called at the end of each frame to prepare for fresh input.
     */
    void reset();

    /**
     * @brief Checks if an action is currently being held down.
     *
     * @param action The name of the action.
     * @return True if the associated key is held, false otherwise.
     */
    bool isActionHeld(const string& action) const;

    /**
     * @brief Checks if an action was pressed in the current frame.
     *
     * @param action The name of the action.
     * @return True if the key was pressed, false otherwise.
     */
    bool wasActionPressed(const string& action) const;

    /**
     * @brief Checks if an action was released in the current frame.
     *
     * @param action The name of the action.
     * @return True if the key was released, false otherwise.
     */
    bool wasActionReleased(const string& action) const;

    /**
     * @brief Returns how long a key has been held down for an action.
     *
     * @param action The name of the action.
     * @return Hold duration in seconds.
     */
    float getHoldDuration(const string& action) const;

    /**
     * @brief Binds a key to a named action.
     *
     * @param action The name of the action.
     * @param key The keyboard key to bind.
     */
    void bindAction(const string& action, sf::Keyboard::Key key);

    /**
     * @brief Gets the key bound to a given action.
     *
     * @param action The name of the action.
     * @return The associated SFML keyboard key.
     */
    sf::Keyboard::Key getKeyForAction(const string& action) const;

private:
    unordered_map<sf::Keyboard::Key, bool> keyHeld;
    unordered_map<sf::Keyboard::Key, bool> keyPressed;
    unordered_map<sf::Keyboard::Key, bool> keyReleased;
    unordered_map<sf::Keyboard::Key, float> keyHoldDuration;

    unordered_map<string, sf::Keyboard::Key> actionBindings;
    unordered_map<sf::Keyboard::Key, string> keyBindings;
};
