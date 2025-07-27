//
// Created by navin on 7/18/25.
//
#pragma once
#include <SFML/Graphics/View.hpp>
#include "../Entity/Entity.h"

namespace cameraBehaviour {
    void cameraTracking(Entity& player, sf::View& camera, float margin, float worldWidth);
}
