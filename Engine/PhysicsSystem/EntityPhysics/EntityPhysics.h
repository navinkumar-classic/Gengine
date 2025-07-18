//
// Created by navin on 7/18/25.
//

#pragma once
#include "../../Entity/Entity.h"

namespace EntityPhysics {
    void applyGravity(Entity& entity, Input& input, float dt);
    void applyDeacceleration(Entity& entity, Input& input, float dt, string action1, string action2);
}