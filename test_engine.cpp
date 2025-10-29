
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
#include "Engine/Scene/SceneType/MenuScene.h"
#include "Engine/UI/UIElementType/ImageUIElement.h"
#include "Engine/UI/UIElementType/TextUIElement.h"


std::shared_ptr<GameScene> main_game(Engine &engine) {
    auto scene = std::make_shared<GameScene>(
        1200,
        800
    );

    scene->setBackgroundTexture("/home/navin/CLionProjects/Gengine/Assets/swamp/Background/Background.png");

    engine.gameState.set<int>("score", 0);
    engine.gameState.set<int>("lives", 3);
    engine.gameState.set<int>("n_coins", 0);

    scene->addUIElement(std::move(
        std::make_unique<TextUIElement>(
            sf::Vector2f(380.f, 15.f),
            64,
            "World",
            engine.fetchFont("DEFAULT"),
            sf::Color::White,
            false, 5, '0'
        )
    ));
    scene->addUIElement(std::move(
        std::make_unique<TextUIElement>(
            sf::Vector2f(405.f, 80.f),
            48,
            "1 x 1",
            engine.fetchFont("DEFAULT"),
            sf::Color::White,
            false, 5, '0'
        )
    ));

    scene->addUIElement(std::move(
        std::make_unique<TextUIElement>(
            sf::Vector2f(80.f, 15.f),
            64,
            "Points",
            engine.fetchFont("DEFAULT"),
            sf::Color::White,
            false, 6, '0'
        )
    ));

    scene->addUIElement(std::move(
        std::make_unique<TextUIElement>(
            sf::Vector2f(80.f, 80.f),
            48,
            "<score>",
            engine.fetchFont("DEFAULT"),
            sf::Color::White,
            true, 6, '0'
        )
    ));

    scene->addUIElement(std::move(
        std::make_unique<ImageUIElement>(
            sf::Vector2f(715.f, 75.f),
            sf::Vector2f(10.f, 10.f),
            sf::Vector2f(10.f, 10.f),
            false,
            "/home/navin/CLionProjects/Gengine/Assets/swamp/AnimatedObjects/Coin.png"
        )
    ));

    scene->addUIElement(std::move(
        std::make_unique<TextUIElement>(
            sf::Vector2f(750.f, 47.f),
            48,
            "x",
            engine.fetchFont("DEFAULT"),
            sf::Color::White,
            true, 1, '0'
        )
    ));

    scene->addUIElement(std::move(
        std::make_unique<TextUIElement>(
            sf::Vector2f(780.f, 50.f),
            48,
            "<n_coins>",
            engine.fetchFont("DEFAULT"),
            sf::Color::White,
            true, 3, '0'
        )
    ));

    scene->addUIElement(std::move(
        std::make_unique<ImageUIElement>(
            sf::Vector2f(960.f, 75.f),
            sf::Vector2f(32.f, 32.f),
            sf::Vector2f(3.f, 3.f),
            false,
            "/home/navin/CLionProjects/Gengine/Assets/pinkMonster/Pink_Monster.png"
        )
    ));

    scene->addUIElement(std::move(
        std::make_unique<TextUIElement>(
            sf::Vector2f(1000.f, 47.f),
            48,
            "x",
            engine.fetchFont("DEFAULT"),
            sf::Color::White,
            true, 1, '0'
        )
    ));

    scene->addUIElement(std::move(
        std::make_unique<TextUIElement>(
            sf::Vector2f(1030.f, 50.f),
            48,
            "<lives>",
            engine.fetchFont("DEFAULT"),
            sf::Color::White,
            true, 2, '0'
        )
    ));

    vector<std::pair<float, float>> coins = {{600, 550}, {700, 550}, {755, 420}, {890, 350}, {1020,350},
{1200, 700}, {1300, 700}, {1400, 700}, {1500, 700}, {1990, 400}, {2290, 270}, {2590, 500}};

    for (auto coin: coins) {
        scene->addEntity(std::move(
            std::make_unique<AnimatedStaticEntity>(
                sf::Vector2f(coin.first, coin.second),
                "coin",
                sf::Vector2i(10, 10),
                0.1,
                sf::Vector2f(5.f, 5.f),
                "/home/navin/CLionProjects/Gengine/Assets/swamp/AnimatedObjects/Coin.png",
                4
            )
        ));
    }

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
            sf::Vector2f(860, 750),
            sf::Vector2f(80, 80),
            std::vector<std::vector<int> >{
                {32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34}
            }, "ground", engine.getRefTexture()
        )
    ));

    scene->addEntity(std::move(
        std::make_unique<StaticEntity>(
            sf::Vector2f(2860, 500),
            sf::Vector2f(80, 80),
            std::vector<std::vector<int> >{
                {1, 2, 2, 2, 2, 2, 2, 2, 2, 3},
                {11, 12, 12, 12, 12, 12, 12, 12, 12, 13},
                {17, 12, 12, 12, 12, 12, 12, 12, 12, 13},
                {11, 12, 12, 12, 12, 12, 12, 12, 12, 13},
                {11, 12, 12, 12, 12, 12, 12, 12, 12, 13},
                {21, 22, 22, 22, 22, 22, 22, 22, 22, 23}
            }, "ground", engine.getRefTexture()
        )
    ));

    vector<std::pair<float, float>> platform = {{1950,450}, {2250, 320}, {2550, 550}};

    for (auto pair : platform) {
        scene->addEntity(std::move(
            std::make_unique<StaticEntity>(
                sf::Vector2f(pair.first, pair.second),
                sf::Vector2f(80, 80),
                std::vector<std::vector<int> >{
                    {39}
                }, "ground", engine.getRefTexture()
            )
        ));
    }

    scene->addEntity(std::move(
        std::make_unique<StaticEntity>(
            sf::Vector2f(400, 332),sf::Vector2f(208, 270),
            std::vector<std::vector<int> >{{71}}, "tree", engine.getRefTexture()
        )
    ));

    scene->addEntity(std::move(
        std::make_unique<StaticEntity>(
            sf::Vector2f(1200, 150),sf::Vector2f(211.5f, 252.f),
            std::vector<std::vector<int> >{{72}}, "tree", engine.getRefTexture()
        )
    ));

    scene->addEntity(std::move(
        std::make_unique<StaticEntity>(
            sf::Vector2f(2800, 228),sf::Vector2f(298.5f, 274.5f),
            std::vector<std::vector<int> >{{73}}, "tree", engine.getRefTexture()
        )
    ));

    vector<std::pair<float, float>> bushs_1 = {{355,570}, {1160, 370}, {2900, 470}};

    for (auto bush: bushs_1) {
        scene->addEntity(std::move(
            std::make_unique<StaticEntity>(
                sf::Vector2f(bush.first, bush.second),
                sf::Vector2f(62, 30),
                std::vector<std::vector<int> >{
                    {81}
                }, "bush", engine.getRefTexture()
            )
        ));
    }

    vector<std::pair<float, float>> bushs_2 = {{290,571}, {1320, 371}, {3120, 471}};

    for (auto bush: bushs_2) {
        scene->addEntity(std::move(
            std::make_unique<StaticEntity>(
                sf::Vector2f(bush.first, bush.second),
                sf::Vector2f(62, 30),
                std::vector<std::vector<int> >{
                    {82}
                }, "bush", engine.getRefTexture()
            )
        ));
    }

    vector<std::pair<float, float>> bushs_3 = {{520,572},{3050, 471}};

    for (auto bush: bushs_3) {
        scene->addEntity(std::move(
            std::make_unique<StaticEntity>(
                sf::Vector2f(bush.first, bush.second),
                sf::Vector2f(60, 30),
                std::vector<std::vector<int> >{
                    {83}
                }, "bush", engine.getRefTexture()
            )
        ));
    }

    vector<std::pair<float, float>> crate_1 = {{420, 550}, {1112, 350}, {1080, 300}};

    for (auto crate: crate_1) {
        scene->addEntity(std::move(
            std::make_unique<StaticEntity>(
                sf::Vector2f(crate.first, crate.second),
                sf::Vector2f(66, 52),
                std::vector<std::vector<int> >{{64}},
                "crate",
                engine.getRefTexture()
            )
        ));
    }

    vector<std::pair<float, float>> crate_2 = {{385, 502}, {1050, 350}};

    for (auto crate: crate_2) {
        scene->addEntity(std::move(
            std::make_unique<StaticEntity>(
                sf::Vector2f(crate.first, crate.second),
                sf::Vector2f(66, 52),
                std::vector<std::vector<int> >{{65}},
                "crate",
                engine.getRefTexture()
            )
        ));
    }

    vector<std::pair<float, float>> ridges = {{900, 700}};
    for (auto ridge: ridges) {
        scene->addEntity(std::move(
            std::make_unique<StaticEntity>(
                sf::Vector2f(ridge.first, ridge.second),
                sf::Vector2f(178, 52),
                std::vector<std::vector<int> >{{91}},
                "ridge",
                engine.getRefTexture()
            )
        ));
    }

    vector<std::pair<float, float>> ladder_1 = {{1090, 697}, {1540, 697}};
    for (auto ladder: ladder_1) {
        scene->addEntity(std::move(
            std::make_unique<StaticEntity>(
                sf::Vector2f(ladder.first, ladder.second),
                sf::Vector2f(55, 55),
                std::vector<std::vector<int> >{{94}},
                "ridge",
                engine.getRefTexture()
            )
        ));
    }

    vector<std::pair<float, float>> ladder_2 = {{1090, 642}, {1540, 642}};
    for (auto ladder: ladder_2) {
        scene->addEntity(std::move(
            std::make_unique<StaticEntity>(
                sf::Vector2f(ladder.first, ladder.second),
                sf::Vector2f(55, 55),
                std::vector<std::vector<int> >{{95}},
                "ridge",
                engine.getRefTexture()
            )
        ));
    }
    scene->addEntity(std::move(
        std::make_unique<StaticEntity>(
            sf::Vector2f(1450, 300),
            sf::Vector2f(132, 104),
            std::vector<std::vector<int> >{{65}},
            "crate",
            engine.getRefTexture()
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
        std::make_unique<AnimatedStaticEntity>(
            sf::Vector2f(3300, 430),
            "flag",
            sf::Vector2i(48, 48),
            0.1,
            sf::Vector2f(3.f, 3.f),
            "/home/navin/CLionProjects/Gengine/Assets/swamp/AnimatedObjects/Flag.png",
            4
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
    player->addPhysics([](Entity &entity, InputManager &input, float dt) {
        EntityPhysics::applyDeacceleration(entity, input, dt, "RIGHT", "LEFT");
    });

    size_t playerId = scene->addEntity(std::move(player));

    scene->addEntity(std::move(
        std::make_unique<StaticEntity>(
            sf::Vector2f(1740, 770),
            sf::Vector2f(80, 80),
            std::vector<std::vector<int> >{
                {40,40,40,40,40,40,40,40,40,40,40,40,40,40}
            }, "water", engine.getRefTexture()
        )
    ));

    engine.collision.addEntryToCollisionHandler("pink_monster", "ground",
                                                CollisionBehaviour::ControllableToStaticCollision);
    engine.collision.addEntryToCollisionHandler("pink_monster", "crate",
                                                CollisionBehaviour::ControllableToStaticCollision);
    engine.collision.addEntryToCollisionHandler("crate", "ground", CollisionBehaviour::ControllableToStaticCollision);

    auto scenePtr = std::weak_ptr<GameScene>(scene);

    auto scene_uid = "scene_" + std::to_string(reinterpret_cast<uintptr_t>(scene.get()));

    engine.collision.addEntryToCollisionHandler("pink_monster", "coin",
                                                [&engine](Entity *a, Entity *b) {
                                                    CollisionBehaviour::ControllableToCollectibleCollision(a, b);
                                                    engine.gameState.increment<int>("score", 100);
                                                    engine.gameState.increment<int>("n_coins", 1);
                                                    engine.music.playSoundEffect("pickup");
                                                });

    engine.event.defineOn("FallDown" + scene_uid,
                          [scenePtr, playerId]() {
                              if (auto shared = scenePtr.lock()) {
                                  return shared->getEntity(playerId)->getPosition().y > 1000;
                              }
                              return false;
                          },
                          [&engine, scenePtr,playerId]() {
                              if (auto shared = scenePtr.lock()) {
                                  engine.gameState.increment<int>("lives", -1);
                                  shared->getEntity(playerId)->setPosition(sf::Vector2f(200, 150));
                              }
                          });

    engine.event.defineOn("GameOver" + scene_uid,
                          [scenePtr, playerId]() {
                              if (auto shared = scenePtr.lock()) {
                                  return shared->getEntity(playerId)->getPosition().x > 3348;
                              }
                              return false;
                          },
                          [&engine, scenePtr,playerId]() {
                              if (auto shared = scenePtr.lock()) {
                                  engine.clearSceneStack();
                                  engine.switchScene("victory");
                              }
                          });

    scene->addCameraBehaviour([](Entity &player, sf::View &camera) {
        cameraBehaviour::cameraTracking(player, camera, 300.0f, 3500.0f);
    }, playerId);

    scene->addEventToDelete("FallDown" + scene_uid);

    engine.music.playMusic("level");

    return scene;
}

std::shared_ptr<MenuScene> start_screen(Engine &engine) {
    auto start = std::make_shared<MenuScene>(1200, 800);

    start->setBackgroundTexture("/home/navin/CLionProjects/Gengine/Assets/swamp/Background/Background.png");

    start->addUIElement(std::move(
        std::make_unique<ImageUIElement>(
            sf::Vector2f(600.f, 400.f),
            sf::Vector2f(83.f, 55.f),
            sf::Vector2f(11.f, 11.f),
            true,
            "/home/navin/CLionProjects/Gengine/Assets/UI/Bonus/Bonus 03.png"
        )
    ));

    start->addUIElement(std::move(
        std::make_unique<TextUIElement>(
            sf::Vector2f(320.f, 150.f),
            120,
            "Swamp",
            engine.fetchFont("DEFAULT"),
            sf::Color::White,
            false, 5, '0'
        )
    ));

    start->addUIElement(std::move(
        std::make_unique<TextUIElement>(
            sf::Vector2f(500.f, 300.f),
            120,
            "Monster",
            engine.fetchFont("DEFAULT"),
            sf::Color::White,
            false, 7, '0'
        )
    ));

    size_t exit_id = start->addUIElement(std::move(
        std::make_unique<ImageUIElement>(
            sf::Vector2f(1007.f, 147.f),
            sf::Vector2f(28.f, 27.f),
            sf::Vector2f(2.f, 2.f),
            true,
            "/home/navin/CLionProjects/Gengine/Assets/UI/Main menu/BTN Exit.png"
        )
    ));

    size_t back_id = start->addUIElement(std::move(
        std::make_unique<ImageUIElement>(
            sf::Vector2f(600.f, 550.f),
            sf::Vector2f(200.f, 48.f),
            sf::Vector2f(2.f, 2.f),
            true,
            "/home/navin/CLionProjects/Gengine/Assets/UI/Main menu/BTN PLAY.png"
        )
    ));

    auto StartPtr = std::weak_ptr<MenuScene>(start);
    auto start_uid = "scene_" + std::to_string(reinterpret_cast<uintptr_t>(start.get()));


    engine.event.defineOn("play_fn" + start_uid, [StartPtr, back_id]() {
                              if (auto shared = StartPtr.lock())
                                  return shared->getUIElement(back_id)->getIsPressed();
                              return false;
                          },
                          [&engine]() {
                              engine.clearSceneStack();
                              engine.switchScene("main");
                          });

    engine.event.defineOn("quit_fn" + start_uid, [StartPtr, exit_id]() {
                              if (auto shared = StartPtr.lock())
                                  return shared->getUIElement(exit_id)->getIsPressed();
                              return false;
                          },
                          [&engine]() {
                              engine.quitEngine();
                          });

    start->addEventToDelete("play_fn" + start_uid);
    start->addEventToDelete("quit_fn" + start_uid);

    engine.music.resumeMusic();
    engine.music.playMusic("menu");

    return start;
}

std::shared_ptr<MenuScene> pause_screen(Engine &engine) {
    auto menu = std::make_shared<MenuScene>(
        1200,
        800
    );

    menu->addUIElement(std::move(
        std::make_unique<ImageUIElement>(
            sf::Vector2f(600.f, 400.f),
            sf::Vector2f(146.f, 183.f),
            sf::Vector2f(3.f, 3.f),
            false,
            "/home/navin/CLionProjects/Gengine/Assets/UI/Pause menu/PAUSE PRESET.png"
        )
    ));

    auto menuPtr = std::weak_ptr<MenuScene>(menu);

    size_t back_id = menu->addUIElement(std::move(
        std::make_unique<ImageUIElement>(
            sf::Vector2f(600.f, 300.f),
            sf::Vector2f(77.f, 35.f),
            sf::Vector2f(2.5f, 2.5f),
            true,
            "/home/navin/CLionProjects/Gengine/Assets/UI/Pause menu/BTN BACK.png"
        )
    ));

    size_t start_id = menu->addUIElement(std::move(
        std::make_unique<ImageUIElement>(
            sf::Vector2f(600.f, 580.f),
            sf::Vector2f(110.f, 35.f),
            sf::Vector2f(2.5f, 2.5f),
            true,
            "/home/navin/CLionProjects/Gengine/Assets/UI/Pause menu/BTN MENU.png"
        )
    ));

    size_t retry_btn_id = menu->addUIElement(std::move(
        std::make_unique<ImageUIElement>(
            sf::Vector2f(600.f, 420.f),
            sf::Vector2f(77.f, 35.f),
            sf::Vector2f(2.5f, 2.5f),
            true,
            "/home/navin/CLionProjects/Gengine/Assets/UI/Mission Failed/BTN Retry.png"
        )
    ));

    auto menu_uid = "scene_" + std::to_string(reinterpret_cast<uintptr_t>(menu.get()));

    engine.event.defineOn("back_fn" + menu_uid, [menuPtr, back_id]() {
                              if (auto shared = menuPtr.lock())
                                  return shared->getUIElement(back_id)->getIsPressed();
                              return false;
                          },
                          [&engine]() {
                              engine.popScene();
                          });

    engine.event.defineOn("retry_fn" + menu_uid, [menuPtr, retry_btn_id]() {
                              if (auto shared = menuPtr.lock())
                                  return shared->getUIElement(retry_btn_id)->getIsPressed();
                              return false;
                          },
                          [&engine]() {
                              engine.clearSceneStack();
                              engine.switchScene("main");
                          });

    engine.event.defineOn("start_fn" + menu_uid, [menuPtr, start_id]() {
                              if (auto shared = menuPtr.lock())
                                  return shared->getUIElement(start_id)->getIsPressed();
                              return false;
                          },
                          [&engine]() {
                              engine.clearSceneStack();
                              engine.switchScene("start");
                          });

    menu->addEventToDelete("retry_fn" + menu_uid);
    menu->addEventToDelete("back_fn" + menu_uid);
    menu->addEventToDelete("start_fn" + menu_uid);

    return menu;
}

std::shared_ptr<MenuScene> defeat_screen(Engine &engine) {
    auto menu = std::make_shared<MenuScene>(
        1200,
        800
    );

    auto menuPtr = std::weak_ptr<MenuScene>(menu);

    menu->addUIElement(std::move(
        std::make_unique<ImageUIElement>(
            sf::Vector2f(600.f, 350.f),
            sf::Vector2f(216.f, 123.f),
            sf::Vector2f(2.5f, 2.5f),
            true,
            "/home/navin/CLionProjects/Gengine/Assets/UI/Mission Failed/BG Preset.png"
        )
    ));

    menu->addUIElement(std::move(
        std::make_unique<TextUIElement>(
            sf::Vector2f(470.f, 215.f),
            48,
            "GAME OVER",
            engine.fetchFont("DEFAULT"),
            sf::Color::White,
            true, 9, '0'
        )
    ));

    menu->addUIElement(std::move(
        std::make_unique<TextUIElement>(
            sf::Vector2f(560.f, 300.f),
            32,
            "<score>",
            engine.fetchFont("DEFAULT"),
            sf::Color::White,
            true, 6, '0'
        )
    ));

    size_t start_id = menu->addUIElement(std::move(
        std::make_unique<ImageUIElement>(
            sf::Vector2f(600.f, 600.f),
            sf::Vector2f(110.f, 35.f),
            sf::Vector2f(2.5f, 2.5f),
            true,
            "/home/navin/CLionProjects/Gengine/Assets/UI/Pause menu/BTN MENU.png"
        )
    ));

    size_t retry_btn_id = menu->addUIElement(std::move(
        std::make_unique<ImageUIElement>(
            sf::Vector2f(600.f, 425.f),
            sf::Vector2f(77.f, 35.f),
            sf::Vector2f(2.5f, 2.5f),
            true,
            "/home/navin/CLionProjects/Gengine/Assets/UI/Mission Failed/BTN Retry.png"
        )
    ));

    auto menu_uid = "scene_" + std::to_string(reinterpret_cast<uintptr_t>(menu.get()));

    engine.event.defineOn("retry_fn" + menu_uid, [menuPtr, retry_btn_id]() {
                              if (auto shared = menuPtr.lock())
                                  return shared->getUIElement(retry_btn_id)->getIsPressed();
                              return false;
                          },
                          [&engine]() {
                              engine.clearSceneStack();
                              engine.switchScene("main");
                          });

    engine.event.defineOn("start_fn" + menu_uid, [menuPtr, start_id]() {
                              if (auto shared = menuPtr.lock())
                                  return shared->getUIElement(start_id)->getIsPressed();
                              return false;
                          },
                          [&engine]() {
                              engine.clearSceneStack();
                              engine.switchScene("start");
                          });

    menu->addEventToDelete("retry_fn" + menu_uid);
    menu->addEventToDelete("start_fn" + menu_uid);

    return menu;
}

std::shared_ptr<MenuScene> victory_screen(Engine &engine) {
    auto menu = std::make_shared<MenuScene>(
        1200,
        800
    );

    auto menuPtr = std::weak_ptr<MenuScene>(menu);

    menu->addUIElement(std::move(
        std::make_unique<ImageUIElement>(
            sf::Vector2f(600.f, 350.f),
            sf::Vector2f(216.f, 123.f),
            sf::Vector2f(2.5f, 2.5f),
            true,
            "/home/navin/CLionProjects/Gengine/Assets/UI/Mission Failed/BG Preset.png"
        )
    ));

    menu->addUIElement(std::move(
        std::make_unique<TextUIElement>(
            sf::Vector2f(500.f, 215.f),
            48,
            "VICTORY",
            engine.fetchFont("DEFAULT"),
            sf::Color::White,
            true, 7, '0'
        )
    ));

    menu->addUIElement(std::move(
        std::make_unique<TextUIElement>(
            sf::Vector2f(560.f, 300.f),
            32,
            "<score>",
            engine.fetchFont("DEFAULT"),
            sf::Color::White,
            true, 6, '0'
        )
    ));

    size_t start_id = menu->addUIElement(std::move(
        std::make_unique<ImageUIElement>(
            sf::Vector2f(600.f, 600.f),
            sf::Vector2f(110.f, 35.f),
            sf::Vector2f(2.5f, 2.5f),
            true,
            "/home/navin/CLionProjects/Gengine/Assets/UI/Pause menu/BTN MENU.png"
        )
    ));

    size_t retry_btn_id = menu->addUIElement(std::move(
        std::make_unique<ImageUIElement>(
            sf::Vector2f(600.f, 425.f),
            sf::Vector2f(77.f, 35.f),
            sf::Vector2f(2.5f, 2.5f),
            true,
            "/home/navin/CLionProjects/Gengine/Assets/UI/Mission Failed/BTN Retry.png"
        )
    ));

    auto menu_uid = "scene_" + std::to_string(reinterpret_cast<uintptr_t>(menu.get()));

    engine.event.defineOn("retry_fn" + menu_uid, [menuPtr, retry_btn_id]() {
                              if (auto shared = menuPtr.lock())
                                  return shared->getUIElement(retry_btn_id)->getIsPressed();
                              return false;
                          },
                          [&engine]() {
                              engine.clearSceneStack();
                              engine.switchScene("main");
                          });

    engine.event.defineOn("start_fn" + menu_uid, [menuPtr, start_id]() {
                              if (auto shared = menuPtr.lock())
                                  return shared->getUIElement(start_id)->getIsPressed();
                              return false;
                          },
                          [&engine]() {
                              engine.clearSceneStack();
                              engine.switchScene("start");
                          });

    menu->addEventToDelete("retry_fn" + menu_uid);
    menu->addEventToDelete("start_fn" + menu_uid);

    return menu;
}

int main() {
    std::unordered_map<int, std::string> ref_texture = {
        {64, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Boxes/4.png"},
        {65, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Boxes/2.png"},
        {71, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Willows/1.png"},
        {72, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Willows/2.png"},
        {73, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Willows/3.png"},
        {81, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Bushes/1.png"},
        {82, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Bushes/2.png"},
        {83, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Bushes/3.png"},
        {84, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Bushes/4.png"},
        {91, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Ridges/1.png"},
        {92, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Ridges/2.png"},
        {93, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Ridges/3.png"},
        {94, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Ladders/1.png"},
        {95, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Ladders/2.png"}
    };

    std::string basePath = "/home/navin/CLionProjects/Gengine/Assets/swamp/Tiles/Tile_";

    for (int i = 1; i <= 60; ++i) {
        std::ostringstream oss;
        oss << basePath << std::setw(2) << std::setfill('0') << i << ".png";
        ref_texture[i] = oss.str();
    }

    Engine engine(1200, 800, "/home/navin/CLionProjects/Gengine/Assets/font/Pixellari.ttf", "Swamp Monster");
    engine.setFrameRate(120);
    engine.setRefTexture(ref_texture);

    engine.input.bindAction("RIGHT", sf::Keyboard::D);
    engine.input.bindAction("LEFT", sf::Keyboard::A);
    engine.input.bindAction("UP", sf::Keyboard::Space);
    engine.input.bindAction("PAUSE", sf::Keyboard::P);

    engine.gameState.set<int>("score", 0);
    engine.gameState.set<int>("lives", 3);
    engine.gameState.set<int>("n_coins", 0);

    engine.music.loadMusic("menu", "/home/navin/CLionProjects/Gengine/Assets/music/8 Bit Japan.wav");
    engine.music.loadMusic("level", "/home/navin/CLionProjects/Gengine/Assets/music/My Love.wav");
    engine.music.loadSoundEffect("jump", "/home/navin/CLionProjects/Gengine/Assets/SFX/8bit-jump1.wav");
    engine.music.loadSoundEffect("pickup", "/home/navin/CLionProjects/Gengine/Assets/SFX/8bit-pickup2.wav");

    engine.addSceneFactory("main", [&engine]() {
        return main_game(engine);
    });

    engine.addSceneFactory("start", [&engine]() {
        return start_screen(engine);
    });

    engine.addSceneFactory("pause", [&engine]() {
        return pause_screen(engine);
    });

    engine.addSceneFactory("defeat", [&engine]() {
        return defeat_screen(engine);
    });

    engine.addSceneFactory("victory", [&engine]() {
        return victory_screen(engine);
    });

    engine.event.defineOn("pause", [&engine]() {
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

    engine.event.defineOn("defeat", [&engine]() {
                              if (engine.gameState.get<int>("lives") <= 0 and engine.getCurrentSceneName() == "main")
                                  return true;
                              return false;
                          }, [&engine]() {
                              engine.clearSceneStack();
                              engine.switchScene("defeat");
                          });

    engine.switchScene("start");
    engine.run();

    return 0;
}
