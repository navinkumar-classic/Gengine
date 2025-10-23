//
// Created by navin on 10/23/25.
//


#include <functional>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "Engine/Engine.h"
#include "Engine/Entity/EntityType/ControllableEntity.h"
#include "Engine/Entity/EntityType/StaticEntity.h"
#include "Utility/Movement.h"
#include "Engine/Scene/SceneType/GameScene.h"
#include "Utility/CollisionBehaviour.h"
#include "Utility/EntityPhysics.h"
#include "Utility/CameraBehaviour.h"
#include "Engine/Entity/EntityType/AnimatedStaticEntity.h"
#include "Engine/UIElement/UIElementType/TextUIElement.h"


std::unique_ptr<GameScene> gg(Engine &engine) {
    auto scene = std::make_unique<GameScene>(
        1200,
        800
    );

    scene->setBackgroundTexture("/home/navin/CLionProjects/Gengine/Assets/swamp/Background/Background.png");

    engine.gameState.set<int>("score", 100);

    scene->addUIElement(std::move(
        std::make_unique<TextUIElement>(
            sf::Vector2f(100.f, 100.f),
            32,
            "Score: <score>",
            engine.fetchFont("DEFAULT"),
            sf::Color::White,
            true
        )
    ));

    scene->addEntity(std::move(
        std::make_unique<AnimatedStaticEntity>(
            sf::Vector2f(600, 550),
            "coin",
            sf::Vector2i(10, 10),
            0.1,
            sf::Vector2f(5.f, 5.f),
            "/home/navin/CLionProjects/Gengine/Assets/swamp/AnimatedObjects/Coin.png",
            4
        )
    ));

    scene->addEntity(std::move(
        std::make_unique<AnimatedStaticEntity>(
            sf::Vector2f(700, 550),
            "coin",
            sf::Vector2i(10, 10),
            0.1,
            sf::Vector2f(5.f, 5.f),
            "/home/navin/CLionProjects/Gengine/Assets/swamp/AnimatedObjects/Coin.png",
            4
        )
    ));

    scene->addEntity(std::move(
        std::make_unique<AnimatedStaticEntity>(
            sf::Vector2f(890, 350),
            "coin",
            sf::Vector2i(10, 10),
            0.1,
            sf::Vector2f(5.f, 5.f),
            "/home/navin/CLionProjects/Gengine/Assets/swamp/AnimatedObjects/Coin.png",
            4
        )
    ));

    scene->addEntity(std::move(
        std::make_unique<AnimatedStaticEntity>(
            sf::Vector2f(775, 450),
            "coin",
            sf::Vector2i(10, 10),
            0.1,
            sf::Vector2f(5.f, 5.f),
            "/home/navin/CLionProjects/Gengine/Assets/swamp/AnimatedObjects/Coin.png",
            4
        )
    ));


    scene->addEntity(std::move(
        std::make_unique<StaticEntity>(
            sf::Vector2f(0, 600),
            sf::Vector2f(80, 80),
            std::vector<std::vector<int> >{
                {1, 28, 28, 2, 2, 2, 10, 2, 28, 3},
                {11, 12, 12, 12, 12, 12, 12, 12, 12, 13},
                {11, 12, 12, 12, 12, 12, 12, 12, 12, 13}
            }, "ground", engine.getRefTexture()
        )
    ));

    scene->addEntity(std::move(
        std::make_unique<StaticEntity>(
            sf::Vector2f(900, 400),
            sf::Vector2f(80, 80),
            std::vector<std::vector<int> >{
                {1, 2, 2, 2, 2, 2, 2, 2, 2, 3},
                {17, 12, 12, 12, 12, 12, 12, 12, 12, 13},
                {21, 22, 22, 22, 22, 22, 22, 22, 22, 23}
            }, "ground", engine.getRefTexture()
        )
    ));

    scene->addEntity(std::move(
        std::make_unique<StaticEntity>(
            sf::Vector2f(400, 332),
            sf::Vector2f(208, 270),
            std::vector<std::vector<int> >{
                {71}
            }, "tree", engine.getRefTexture()
        )
    ));

    scene->addEntity(std::move(
        std::make_unique<StaticEntity>(
            sf::Vector2f(355, 570),
            sf::Vector2f(62, 30),
            std::vector<std::vector<int> >{
                {81}
            }, "bush", engine.getRefTexture()
        )
    ));

    scene->addEntity(std::move(
        std::make_unique<StaticEntity>(
            sf::Vector2f(290, 580),
            sf::Vector2f(60, 20),
            std::vector<std::vector<int> >{
                {82}
            }, "bush", engine.getRefTexture()
        )
    ));

    scene->addEntity(std::move(
        std::make_unique<StaticEntity>(
            sf::Vector2f(520, 572),
            sf::Vector2f(60, 30),
            std::vector<std::vector<int> >{
                {83}
            }, "bush", engine.getRefTexture()
        )
    ));

    scene->addEntity(std::move(
        std::make_unique<StaticEntity>(
            sf::Vector2f(860, 750),
            sf::Vector2f(80, 80),
            std::vector<std::vector<int> >{
                {32, 33, 33, 33, 33, 33, 33, 33, 33, 34}
            }, "ground", engine.getRefTexture()
        )
    ));

    auto player = std::make_unique<ControllableEntity>(
        true,
        sf::Vector2f(200.0f, 150.0f),
        sf::Vector2f(0.0f, 0.0f),
        sf::Vector2f(0.0f, 1200.0f),
        300.0f,
        900.0f,
        -1100.0f,
        750.0f,
        3000.0f,
        sf::Vector2u(800.0f, 600.0f),
        32,
        32,
        0.1,
        sf::Vector2f(2.5f, 2.5f),
        "pink_monster"
    );
    player->addAction("UP", Movement::moveJump);
    player->addAction("RIGHT", Movement::moveRight);
    player->addAction("LEFT", Movement::moveLeft);

    player->Sprite.addTexture("DEFAULT", "/home/navin/CLionProjects/Gengine/Assets/pinkMonster/Pink_Monster_Idle_4.png",
                              4);
    player->Sprite.addTexture("WALK", "/home/navin/CLionProjects/Gengine/Assets/pinkMonster/Pink_Monster_Walk_6.png",
                              6);
    player->Sprite.addTexture("JUMP", "/home/navin/CLionProjects/Gengine/Assets/pinkMonster/Pink_Monster_Jump_8.png",
                              8);

    player->addPhysics(EntityPhysics::applyGravity);
    player->addPhysics([](Entity &entity, Input &input, float dt) {
        EntityPhysics::applyDeacceleration(entity, input, dt, "RIGHT", "LEFT");
    });

    size_t playerId = scene->addEntity(std::move(player));

    auto crate1 = std::make_unique<StaticEntity>(
        true,
        sf::Vector2f(450, 0),
        sf::Vector2f(0.0f, 0.0f),
        sf::Vector2f(0.0f, 1100.0f),
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        sf::Vector2f(66, 52),
        std::vector<std::vector<int> >{
            {64}
        },
        "crate",
        engine.getRefTexture()
    );
    crate1->addPhysics(EntityPhysics::applyGravity);
    scene->addEntity(std::move(crate1));

    engine.collision.addEntryToCollisionHandler("pink_monster", "ground",
                                                CollisionBehaviour::ControllableToStaticCollision);
    engine.collision.addEntryToCollisionHandler("pink_monster", "crate",
                                                CollisionBehaviour::ControllableToStaticCollision);
    engine.collision.addEntryToCollisionHandler("crate", "ground", CollisionBehaviour::ControllableToStaticCollision);

    GameScene *scenePtr = scene.get();

    engine.collision.addEntryToCollisionHandler("pink_monster", "coin",
                                                [scenePtr, &engine](Entity *a, Entity *b) {
                                                    CollisionBehaviour::ControllableToCollectibleCollision(a, b);
                                                    engine.gameState.increment<int>("score", 100);
                                                });

    engine.event.defineOn("FallDown",
                          [scenePtr, playerId]() {
                              return scenePtr->getEntity(playerId)->getPosition().y > 1000;
                          },
                          [scenePtr,playerId]() {
                              scenePtr->getEntity(playerId)->setPosition(sf::Vector2f(0, 0));
                          });

    scene->addCameraBehaviour([](Entity &player, sf::View &camera) {
        cameraBehaviour::cameraTracking(player, camera, 200.0f, 2000.0f);
    }, playerId);

    scenePtr = nullptr;
    return scene;
}

int main() {
    std::unordered_map<int, std::string> ref_texture = {
        {64, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Boxes/4.png"},
        {71, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Willows/1.png"},
        {81, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Bushes/1.png"},
        {82, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Bushes/2.png"},
        {83, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Bushes/3.png"},
        {84, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Bushes/4.png"},
        {85, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Bushes/5.png"},
        {86, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Bushes/6.png"},
        {87, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Bushes/7.png"},
        {88, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Bushes/8.png"},
        {89, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Bushes/9.png"},
        {91, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Fence/1.png"},
        {92, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Fence/2.png"},
        {93, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Fence/3.png"}
    };

    std::string basePath = "/home/navin/CLionProjects/Gengine/Assets/swamp/Tiles/Tile_";

    for (int i = 1; i <= 60; ++i) {
        std::ostringstream oss;
        oss << basePath << std::setw(2) << std::setfill('0') << i << ".png";
        ref_texture[i] = oss.str();
    }

    Engine engine(1200, 800, "/home/navin/CLionProjects/Gengine/Assets/font/Pixellari.ttf", "Title");
    engine.setFrameRate(120);
    engine.setRefTexture(ref_texture);

    engine.input.bindAction("RIGHT", sf::Keyboard::D);
    engine.input.bindAction("LEFT", sf::Keyboard::A);
    engine.input.bindAction("UP", sf::Keyboard::Space);
    engine.input.bindAction("PAUSE", sf::Keyboard::P);

    engine.addSceneFactory("main", [&engine]() {
        return gg(engine);
    });

    engine.addSceneFactory("pause", []() {
        return std::make_unique<GameScene>(
            1200,
            800
        );
    });

    engine.switchScene("main");

    engine.event.defineOn("pause",[&engine]() {
        if (engine.input.wasActionPressed("PAUSE"))
            return true;
        return false;
    },
    [&engine]() {
        if (engine.getCurrentSceneName() == "main")
            engine.pushSwitchScene("pause");
        else
            engine.popScene();
    });

    engine.run();

    return 0;
}
