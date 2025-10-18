//
// Created by navin on 7/21/25.
//
#include <memory>
#include <iostream>
#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(
    int frameWidth,
    int frameHeight,
    float frameDuration
    ):
    frameSize(sf::Vector2i(frameWidth,frameHeight)),
    frameDuration(frameDuration)
{
    sprite.setScale(2.f, 2.f);
}

void AnimatedSprite::addTexture(std::string action, std::string texturePath, int totalFrames) {

    auto texture = std::make_shared<sf::Texture>();
    if (texture->loadFromFile(texturePath)) {
        textureMap.insert({action, {texture, totalFrames}});
    } else {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }

    if (action == "DEFAULT") {
        setTextureToSprite("DEFAULT");
    }
}

void AnimatedSprite::setTextureToSprite(std::string action) {
    sprite.setTexture(*textureMap[action].first);
    sprite.setTextureRect(sf::IntRect(0, 0, frameSize.x, frameSize.y));

    //changes centre
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, 0.f);

    frameTimer = 0;
    totalFrames = textureMap[action].second;
    currentFrame = 0;
    currentAction = action;
}

void AnimatedSprite::update(float dt) {

    frameTimer += dt;
    if (frameTimer >= frameDuration) {
        frameTimer = 0.f;
        currentFrame = (currentFrame + 1) % totalFrames;
        sprite.setTextureRect(sf::IntRect(currentFrame * frameSize.x, 0, frameSize.x, frameSize.y));
    }
}

void AnimatedSprite::draw(sf::RenderWindow& window) {

    window.draw(sprite);
}

void AnimatedSprite::setPosition(const sf::Vector2f &pos) {

    sprite.setPosition(pos);
}

sf::FloatRect AnimatedSprite::getBounds() const {

    return sprite.getGlobalBounds();
}

std::string AnimatedSprite::getCurrentAction() {

    return currentAction;
}

void AnimatedSprite::flipToLeft() {
    sprite.setScale(-2.f, 2.f);
}

void AnimatedSprite::flipToRight() {
    sprite.setScale(2.f, 2.f);
}




