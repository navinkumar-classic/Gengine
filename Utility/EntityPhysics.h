//
// Created by navin on 7/18/25.
//

#pragma once
#include "../Engine/Entity/Entity.h"

namespace EntityPhysics {
    void applyGravity(Entity& entity, InputManager& input, float dt);
    void applyDeacceleration(Entity& entity, InputManager& input, float dt, string action1, string action2);
}