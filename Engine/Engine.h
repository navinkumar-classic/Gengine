//
// Created by navin on 7/14/25.
//
#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Input/Input.h"
#include "Entity/Entity.h"

/**
 * @class Engine
 * @brief Central class that drives the game loop, rendering, and input/event handling.
 *
 * The Engine coordinates core subsystems: window creation, input processing,
 * entity updates, and rendering. It serves as the main runtime environment
 * for the game.
 */
class Engine {
public:
    /**
     * @brief Creates a game engine with a given window size.
     * @param width Width of the window in pixels.
     * @param height Height of the window in pixels.
     */
    Engine(unsigned int width = 800, unsigned int height = 600);

    /**
     * @brief Starts and runs the main game loop.
     *
     * Continuously processes events, updates entity state,
     * and renders frames until the engine is stopped.
     */
    void run();

    /**
     * @brief Adds a new entity to the engine's world.
     * @param entity A unique pointer to the entity to be added.
     */
    void addEntity(std::unique_ptr<Entity> entity);

private:
    /**
     * @brief Handles input events and stores the input state to be used in the update().
     * @param dt Time elapsed since the last frame.
     */
    void processEvents(float dt);

    /**
     * @brief Updates the state of all entities in the engine.
     *
     * This method processes input, applies game logic, updates entity positions,
     * and runs the collision system to handle interactions between entities.
     *
     * @param dt Time delta since the last frame (in seconds).
     */
    void update(float dt);

    /**
     * @brief Renders all visible entities to the window.
     */
    void render();

    bool isRunning = true;

    sf::RenderWindow window;
    sf::View camera;
    sf::Clock clock;
    Input input;
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<Entity*> movableEntities;
};
