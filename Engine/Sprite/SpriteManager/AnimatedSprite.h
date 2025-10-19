//
// Created by navin on 7/21/25.
//

#pragma once
#include "../SpriteBase.h"
#include <memory>

class AnimatedSprite : public SpriteBase {

public:
    AnimatedSprite(
        int frameWidth,
        int frameHeight,
        float frameDuration,
        const sf::Vector2f& scale);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

    void setPosition(const sf::Vector2f& pos) override;
    void setTextureToSprite(std::string action);
    void addTexture(std::string action, std::string texturePath, int totalFrames);

    sf::FloatRect getBounds() const override;
    std::string getCurrentAction();

    void flipToLeft();
    void flipToRight();

private:
    sf::Sprite sprite;
    std::map<std::string, std::pair<std::shared_ptr<sf::Texture>, int>> textureMap;

    int currentFrame = 0;
    int totalFrames = 6;
    float frameDuration = 0.1f;
    float frameTimer = 0.f;

    sf::Vector2i frameSize;
    std::string currentAction;
    sf::Vector2f scale;
};