//
// Created by navin on 10/23/25.
//

#pragma once
#include <functional>
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "GameState/GameState.h"
#include "Input/Input.h"
#include "Scene/Scene.h"
#include "Scene/SceneType/GameScene.h"
#include  "Physics/Collision/Collision.h"

class Engine {
public:
    Engine(unsigned int width, unsigned int height, const std::string &fontPath, const std::string &title);

    void run();

    sf::RenderWindow &getWindow();

    Input &getInput();

    void setFrameRate(int frameRate);

    void addFont(const std::string &key, const std::string &fontPath);

    const sf::Font &fetchFont(const std::string &key);

    void setRefTexture(std::unordered_map<int, std::string> ref_texture);

    const std::unordered_map<int, std::string> &getRefTexture() const;

    void addSceneFactory(const string &name, std::function<std::shared_ptr<Scene>()> factory);

    void switchScene(const string &name);

    void pushSwitchScene(const string &name);

    void clearSceneStack();

    void popScene();

    float clockRestart();

    const std::string &getCurrentSceneName();

    void quitEngine();

    GameState gameState;
    EventManager event;
    Input input;
    Collision collision;

private:
    void processEngineEvents(float dt);

    sf::Clock clock;
    bool isRunning = true;

    sf::RenderWindow window;
    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<int, std::string> ref_texture;

    std::unordered_map<std::string, std::function<std::shared_ptr<Scene>()> > sceneFactory;
    std::shared_ptr<Scene> currentScene;
    std::string currentSceneName;
    std::stack<std::pair<std::string, std::shared_ptr<Scene>>> sceneStack;
};
