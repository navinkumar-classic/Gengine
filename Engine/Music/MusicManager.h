//
// Created by navin on 10/26/25.
//

#pragma once
#include <list>
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

class MusicManager {
public:
    bool loadMusic(const std::string& name, const std::string& filepath);
    bool loadSoundEffect(const std::string& name, const std::string& filepath);

    void playMusic(const std::string& name, bool loop = true);
    void stopMusic() const;
    void pauseMusic() const;
    void resumeMusic() const;

    void playSoundEffect(const std::string& name);

    void update();

private:
    std::unordered_map<std::string, std::string> musicFiles;
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;

    std::unique_ptr<sf::Music> currentMusic;
    std::list<sf::Sound> activeSounds;
    sf::Sound* getAvailableSound();
};
