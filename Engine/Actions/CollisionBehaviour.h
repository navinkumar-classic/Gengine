//
// Created by navin on 7/16/25.
//

#pragma once
#include "../Entity/Entity.h"

namespace CollisionBehaviour {

    void ControllableToStaticCollision(Entity* a, Entity* b);
    void ControllableToControllableCollision(Entity* a, Entity* b);

}
