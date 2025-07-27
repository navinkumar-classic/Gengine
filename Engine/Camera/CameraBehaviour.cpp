//
// Created by navin on 7/18/25.
//

#include "CameraBehaviour.h"

void cameraBehaviour::cameraTracking(Entity& player, sf::View& camera, float margin, float worldWidth) {
    sf::Vector2f playerPos = player.getPosition();
    float playerCenterX = playerPos.x + player.getBounds().width / 2;

    float cameraX = camera.getCenter().x;
    float cameraLeft = cameraX - camera.getSize().x / 2.0f;
    float cameraRight = cameraX + camera.getSize().x / 2.0f;

    if (playerCenterX < cameraLeft + margin) {
        cameraX = playerCenterX - margin + camera.getSize().x / 2.0f;
    } else if (playerCenterX > cameraRight - margin) {
        cameraX = playerCenterX + margin - camera.getSize().x / 2.0f;
    }

    float halfWidth = camera.getSize().x / 2.0f;
    cameraX = std::max(cameraX, halfWidth);
    cameraX = std::min(cameraX, worldWidth - halfWidth);

    camera.setCenter(cameraX, camera.getCenter().y);
}