//
// Created by navin on 7/15/25.
//

#pragma once
#include <memory>
#include <vector>
#include "../Entity/Entity.h"

class EntityInitializer {
    public:
        static std::vector<std::unique_ptr<Entity>> CreateEntityInitialization(sf::Vector2u windowSize);
};
