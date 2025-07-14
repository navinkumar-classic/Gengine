#include <SFML/Graphics.hpp>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");
    sf::Clock clock;

    // Create a circle shape
    sf::CircleShape circle(100.f); // radius
    circle.setFillColor(sf::Color::Red);
    circle.setPointCount(100);
    circle.setPosition(0.f, 400.f);

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2f pos = circle.getPosition();
        while (window.pollEvent(event)) {
            // Close window or press ESC
            if (event.type == sf::Event::Closed ||
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)) {
                window.close();
               }
        }

        const float speed = 200.f;
        float dt = clock.restart().asSeconds();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
            pos.x += speed * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            pos.x -= speed * dt;
        }

        circle.setPosition(pos);

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }

    return 0;
}