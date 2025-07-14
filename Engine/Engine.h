//
// Created by navin on 7/14/25.
//
#pragma once

#include <SFML/Graphics.hpp>

#include "Input/Input.h"

class Engine {
public:
    Engine(unsigned int width = 800, unsigned int height = 600);
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();

    bool isRunning = true;

    sf::RenderWindow window;
    sf::CircleShape circle;
    sf::Clock clock;
    Input input;
};
