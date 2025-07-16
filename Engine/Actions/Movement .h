//
// Created by navin on 7/15/25.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "../Input/Input.h"

namespace Movement {
    void moveLeft(sf::Vector2f& position, sf::Vector2f& velocity, float dt, float maxSpeed, float acceleration, float deacceleration, bool& onGround, float jumpStrength, Input& input, string action);
    void moveRight(sf::Vector2f& position, sf::Vector2f& velocity, float dt, float maxSpeed, float acceleration, float deacceleration, bool& onGround, float jumpStrength, Input& input, string action);
    void moveJump(sf::Vector2f& position, sf::Vector2f& velocity, float dt, float maxSpeed, float acceleration, float deacceleration, bool& onGround, float jumpStrength, Input& input, string action);

    void applyMovement(sf::Vector2f& position, sf::Vector2f& velocity, float dt);
    void applyDeacceleration(sf::Vector2f& velocity, float dt, float deacceleration, bool& onGround, Input& input, string action1, string action2);

};
