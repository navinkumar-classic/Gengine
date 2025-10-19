//
// Created by navin on 7/15/25.
//

#pragma once
#include <memory>
#include <vector>
#include "../../Entity/Entity.h"
#include <SFML/System/Vector2.hpp>

/**
 * @brief Static class responsible for detecting and handling collisions between entities.
 *
 * The Collision system performs broad and narrow phase collision detection among game entities.
 * Only movable entities are tested against all others.
 */
class Collision {
public:
    /**
     * @brief Detects and processes collisions between movable and other entities.
     *
     * This method loops through all movable entities and checks for overlaps
     * with other entities. On collision, appropriate resolution logic is invoked.
     *
     * @param entities All entities present in the scene.
     * @param movableEntities Subset of entities that can move and are considered for collision resolution.
     */
    void collisionManager(const std::vector<std::unique_ptr<Entity>>& entities,
                                const std::vector<Entity*>& movableEntities);

    static string makeKey(const string& a, const string& b);

    void addEntryToCollisionHandler(const string& a, const string& b, const std::function<void(Entity*, Entity*)>& handler);

private:
    /**
     * @brief Checks if two entities are colliding.
     *
     * Typically uses bounding box or shape-based detection.
     *
     * @param a First entity.
     * @param b Second entity.
     * @return True if the entities collide; false otherwise.
     */
    static bool checkCollision(const Entity* a, const Entity* b);

    /**
     * @brief Resolves the collision between two entities.
     *
     * This may include position correction, velocity adjustments, or
     * triggering specific game logic based on entity types.
     *
     * @param a First entity (usually movable).
     * @param b Second entity.
     */
    void handleCollision(Entity* a, Entity* b);

    std::unordered_map<std::string, std::function<void(Entity*, Entity*)>> collisionHandlerMap;
};
