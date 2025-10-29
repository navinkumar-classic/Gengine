//
// Created by navin on 10/26/25.
//

#include "MusicManager.h"
#include <iostream>

bool MusicManager::loadMusic(const std::string& name, const std::string& filepath) {
    musicFiles[name] = filepath;
    return true;
}

bool MusicManager::loadSoundEffect(const std::string& name, const std::string& filepath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filepath)) {
        std::cerr << "Failed to load sound: " << filepath << "\n";
        return false;
    }
    soundBuffers[name] = std::move(buffer);
    return true;
}

void MusicManager::playMusic(const std::string& name, bool loop) {
    auto it = musicFiles.find(name);
    if (it == musicFiles.end()) {
        std::cerr << "Music not found: " << name << "\n";
        return;
    }

    if (currentMusic)
        currentMusic.reset();

    currentMusic = std::make_unique<sf::Music>();
    if (!currentMusic->openFromFile(it->second)) {
        std::cerr << "Failed to open music: " << it->second << "\n";
        return;
    }

    currentMusic->setLoop(loop);
    currentMusic->play();
}

void MusicManager::stopMusic() const {
    if (currentMusic) currentMusic->stop();
}

void MusicManager::pauseMusic() const {
    if (currentMusic) currentMusic->pause();
}

void MusicManager::resumeMusic() const {
    if (currentMusic && currentMusic->getStatus() == sf::Music::Paused)
        currentMusic->play();
}

sf::Sound* MusicManager::getAvailableSound() {
    // Reuse stopped sounds to avoid growing indefinitely
    for (auto& s : activeSounds) {
        if (s.getStatus() == sf::Sound::Stopped)
            return &s;
    }

    // Otherwise create a new one
    activeSounds.emplace_back();
    return &activeSounds.back();
}

void MusicManager::playSoundEffect(const std::string& name) {
    auto it = soundBuffers.find(name);
    if (it == soundBuffers.end()) {
        std::cerr << "Sound effect not found: " << name << "\n";
        return;
    }

    sf::Sound* sound = getAvailableSound();
    sound->setBuffer(it->second);
    sound->setVolume(100.0f);
    sound->play();
}

void MusicManager::update() {
    // Optional with sound pooling, but still clean up if needed
    for (auto it = activeSounds.begin(); it != activeSounds.end();) {
        if (it->getStatus() == sf::Sound::Stopped)
            it = activeSounds.erase(it);
        else
            ++it;
    }
}
