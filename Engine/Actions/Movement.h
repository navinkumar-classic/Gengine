//
// Created by navin on 7/15/25.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "../Input/Input.h"
#include "../Entity/EntityType/ControllableEntity.h"

namespace Movement {
    void moveLeft(ControllableEntity& entity, Input& input, string action, float dt);
    void moveRight(ControllableEntity& entity, Input& input, string action, float dt);
    void moveJump(ControllableEntity& entity, Input& input, string action, float dt);
};
