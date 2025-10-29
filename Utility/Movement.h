//
// Created by navin on 7/15/25.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "../Engine/Input/InputManager.h"
#include "../Engine/Entity/EntityType/ControllableEntity.h"

namespace Movement {
    void moveLeft(ControllableEntity& entity, InputManager& input, MusicManager& music, const string& action, float dt);
    void moveRight(ControllableEntity& entity, InputManager& input, MusicManager& music, const string& action, float dt);
    void moveJump(ControllableEntity& entity, InputManager& input, MusicManager& music, const string& action, float dt);
};
