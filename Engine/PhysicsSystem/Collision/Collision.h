//
// Created by navin on 7/15/25.
//

#pragma once
#include <memory>
#include <vector>
#include "../../Entity/Entity.h"
#include <SFML/System/Vector2.hpp>

class Collision {
    public:
        static void detectCollision(const std::vector<std::unique_ptr<Entity>>& entities,const std::vector<Entity*>& movableEntities);

    private:
        static bool checkCollision(const Entity* a, const Entity* b);
        static void handleCollision(Entity* a, Entity* b);
};
