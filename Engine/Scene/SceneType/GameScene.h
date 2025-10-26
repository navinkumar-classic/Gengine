//
// Created by navin on 7/14/25.
//
#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "../Scene.h"
#include "../../Entity/Entity.h"
#include "../../Event/EventManager.h"

/**
 * @class GameScene
 * @brief Central class that drives the game loop, rendering, and input/event handling.
 *
 * The Engine coordinates core subsystems: window creation, input processing,
 * entity updates, and rendering. It serves as the main runtime environment
 * for the game.
 */
class GameScene: public Scene {
public:
    /**
     * @brief Creates a game engine with a given window size.
     * @param width Width of the window in pixels.
     * @param height Height of the window in pixels.
     */
    explicit GameScene(unsigned int width, unsigned int height);

    /**
     * @brief Starts and runs the main game loop.
     *
     * Continuously processes events, updates entity state,
     * and renders frames until the engine is stopped.
     */
    void init() override;

    void onResume() override;

    void onExit(Engine& engine) override;

    void onPause(Engine& engine) override;

    void update(Engine& engine, float dt) override;

    void render(Engine& engine) override;

    size_t addEntity(std::unique_ptr<Entity> entity);

    Entity* getEntity(size_t id) const;

    void addCameraBehaviour(std::function<void(Entity&, sf::View&)> inputCameraFunction, size_t entity_id);

private:

    sf::View camera;

    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<Entity*> movableEntities;
    std::vector<Entity*> animatedEntities;
    Entity* trackingEntity;

    std::function<void(Entity&, sf::View&)> cameraFunction;

};
