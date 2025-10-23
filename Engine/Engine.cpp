//
// Created by navin on 10/23/25.
//

#include "Engine.h"
#include <iostream>
#include "Scene/Scene.h"
#include "Scene/SceneType/GameScene.h"

Engine::Engine(
    unsigned int width,
    unsigned int height,
    const std::string &fontPath,
    const std::string &title): window(sf::VideoMode(width, height), title){
        addFont("DEFAULT", fontPath);
}

sf::RenderWindow& Engine::getWindow() {
    return window;
}

Input& Engine::getInput() {
    return input;
}

void Engine::addFont(const std::string& key, const std::string& fontPath) {
    sf::Font temp;
    temp.loadFromFile(fontPath);
    fonts[key] = temp;
}

const sf::Font& Engine::fetchFont(const std::string& key) {
    auto it = fonts.find(key);
    if (it != fonts.end()) {
        return it->second;
    }
    std::cerr << "Failed to find font for key " << key << "\n";

    return fonts["DEFAULT"];
}

void Engine::setFrameRate(int frameRate) {
    window.setFramerateLimit(frameRate);
}

void Engine::addSceneFactory(const std::string& name, std::function<std::unique_ptr<Scene>()> factory) {
    sceneFactory[name] = std::move(factory);
}

void Engine::switchScene(const std::string& name) {

    if (currentScene) {
        currentScene->onExit();
        currentScene.reset();
    }

    auto it = sceneFactory.find(name);
    if (it != sceneFactory.end()) {
        currentScene = it->second();
        currentSceneName = name;
    } else {
        std::cerr << "Scene not found: " << name << "\n";
    }
}

void Engine::run() {
    if (currentScene) {
        while (isRunning) {
            float dt = clockRestart();

            processEngineEvents(dt);
            currentScene->update(*this, dt);
            currentScene->render(*this);

            input.reset();
        }
    }
    else {
        std::cerr << "Scene not found\n";
    }
}

float Engine::clockRestart() {
    return clock.restart().asSeconds();
}

void Engine::setRefTexture(std::unordered_map<int, std::string> inp_ref_texture) {
    ref_texture = inp_ref_texture;
}

const std::unordered_map<int, std::string>& Engine::getRefTexture() const {
    return ref_texture;
}

void Engine::processEngineEvents(float dt) {

    sf::Event curEvent{};
    vector<sf::Event> eventList;

    while (window.pollEvent(curEvent)) {

        if (curEvent.type == sf::Event::Closed ||
           (curEvent.type == sf::Event::KeyPressed && curEvent.key.code == sf::Keyboard::Q)) {
            isRunning = false;
            window.close();
           }

        eventList.push_back(curEvent);
    }

    input.updateEvent(eventList, dt);
    event.update(dt);
}

void Engine::pushSwitchScene(const string& name) {
    currentScene->onPause();
    sceneStack.emplace(currentSceneName, std::move(currentScene));
    switchScene(name);
}

void Engine::popScene() {
    if (currentScene) {
        currentScene->onExit();
        currentScene.reset();
    }

    currentScene = std::move(sceneStack.top().second);
    currentSceneName = sceneStack.top().first;
    sceneStack.pop();
}

const std::string& Engine::getCurrentSceneName() {
    return currentSceneName;
}