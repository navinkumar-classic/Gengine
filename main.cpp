
#include <functional>
#include "Engine/Entity/EntityType/ControllableEntity.h"
#include "Engine/Entity/EntityType/StaticEntity.h"
#include "Util/Movement.h"
#include "Engine/Engine.h"
#include "Util/CollisionBehaviour.h"
#include "Util/EntityPhysics.h"


int main() {
    Engine engine(1200,800);

    engine.setFrameRate(120);

    engine.bindAction("RIGHT",sf::Keyboard::D);
    engine.bindAction("LEFT",sf::Keyboard::A);
    engine.bindAction("UP",sf::Keyboard::Space);

    auto player = std::make_unique<ControllableEntity>(
        true,
        sf::Vector2f(200.0f, 150.0f),
        sf::Vector2f(0.0f, 0.0f),
        sf::Vector2f(0.0f, 1100.0f),
        300.0f,
        900.0f,
        -900.0f,
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

    player->Sprite.addTexture("DEFAULT","/home/navin/CLionProjects/Gengine/Assets/pinkMonster/Pink_Monster_Idle_4.png",4 );
    player->Sprite.addTexture("WALK","/home/navin/CLionProjects/Gengine/Assets/pinkMonster/Pink_Monster_Walk_6.png",6 );
    player->Sprite.addTexture("JUMP","/home/navin/CLionProjects/Gengine/Assets/pinkMonster/Pink_Monster_Jump_8.png",8 );

    player->addPhysics(EntityPhysics::applyGravity);
    player->addPhysics([](Entity& entity, Input& input, float dt){EntityPhysics::applyDeacceleration(entity, input, dt, "RIGHT", "LEFT");});

    engine.addEntity(std::move(player));

    std::vector<std::vector<int>> wall1_tilemat = {
        {1,2,2,2,2,2,2,2,2,2,2,3},
        {4,5,5,5,5,5,5,5,5,5,5,6},
        {12,9,9,9,9,9,9,9,9,9,9,16}
    };
    auto wall1 = std::make_unique<StaticEntity>(
        false,
        sf::Vector2f(50, 500),
        sf::Vector2f(0.0f, 0.0f),
        sf::Vector2f(0.0f, 0.0f),
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        sf::Vector2f(96, 96),
        wall1_tilemat,
        "ground"
    );

    wall1->tileMap.loadTexture(1, "/home/navin/CLionProjects/Gengine/Assets/tileSet/png/Tiles/1.png");
    wall1->tileMap.loadTexture(2, "/home/navin/CLionProjects/Gengine/Assets/tileSet/png/Tiles/2.png");
    wall1->tileMap.loadTexture(3, "/home/navin/CLionProjects/Gengine/Assets/tileSet/png/Tiles/3.png");
    wall1->tileMap.loadTexture(4, "/home/navin/CLionProjects/Gengine/Assets/tileSet/png/Tiles/4.png");
    wall1->tileMap.loadTexture(5, "/home/navin/CLionProjects/Gengine/Assets/tileSet/png/Tiles/5.png");
    wall1->tileMap.loadTexture(6, "/home/navin/CLionProjects/Gengine/Assets/tileSet/png/Tiles/6.png");
    wall1->tileMap.loadTexture(12, "/home/navin/CLionProjects/Gengine/Assets/tileSet/png/Tiles/12.png");
    wall1->tileMap.loadTexture(9, "/home/navin/CLionProjects/Gengine/Assets/tileSet/png/Tiles/9.png");
    wall1->tileMap.loadTexture(16, "/home/navin/CLionProjects/Gengine/Assets/tileSet/png/Tiles/16.png");

    engine.addEntity(std::move(wall1));

    std::vector<std::vector<int>> wall2_tilemat = {
        {0}
    };

    auto wall2 = std::make_unique<StaticEntity>(
        true,
        sf::Vector2f(200, 0),
        sf::Vector2f(0.0f, 0.0f),
        sf::Vector2f(0.0f, 1100.0f),
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        sf::Vector2f(96, 96),
        wall2_tilemat,
        "crate"
    );

    wall2->tileMap.loadTexture(0, "/home/navin/CLionProjects/Gengine/Assets/tileSet/png/Object/Crate.png");
    wall2->addPhysics(EntityPhysics::applyGravity);

    engine.addEntity(std::move(wall2));

    engine.addEntryToCollisionHandler("pink_monster", "ground", CollisionBehaviour::ControllableToStaticCollision);
    engine.addEntryToCollisionHandler("pink_monster", "crate", CollisionBehaviour::ControllableToStaticCollision);
    engine.addEntryToCollisionHandler("crate", "ground", CollisionBehaviour::ControllableToStaticCollision);

    engine.run();

    return 0;
}
