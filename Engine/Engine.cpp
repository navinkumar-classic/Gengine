//
// Created by navin on 7/14/25.
//

#include "Engine.h"

Engine::Engine(unsigned int width, unsigned int height)
    : window(sf::VideoMode(width, height), "SFML Test"),
      circle(100.f)
{
    circle.setFillColor(sf::Color::Red);
    circle.setPointCount(100);
    circle.setPosition(0.f, 400.f);
    input.bindAction("RIGHT",sf::Keyboard::Right);
    input.bindAction("LEFT",sf::Keyboard::Left);
}

void Engine::run() {

    while (isRunning) {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }

}

void Engine::processEvents() {
    sf::Event event{};
    vector<sf::Event> events;

    while (window.pollEvent(event)) {
        // Close window or press ESC
        if (event.type == sf::Event::Closed ||
           (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)) {
            isRunning = false;
            window.close();
           }

        events.push_back(event);
    }

    input.updateEvent(events);
}

void Engine::update(float dt) {

    sf::Vector2f pos = circle.getPosition();
    const float speed = 200.f;

    if (input.isActionHeld("RIGHT")) {
        pos.x += speed * dt;
    }
    if (input.isActionHeld("LEFT")) {
        pos.x -= speed * dt;
    }

    circle.setPosition(pos);
    input.reset();
}

void Engine::render() {
    window.clear(sf::Color::Black);
    window.draw(circle);
    window.display();
}
