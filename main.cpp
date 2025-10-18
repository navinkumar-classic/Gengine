
#include <functional>
#include "Engine/Entity/EntityType/ControllableEntity.h"
#include "Engine/Entity/EntityType/StaticEntity.h"
#include "Util/Movement.h"
#include "Engine/Engine.h"
#include "Util/EntityPhysics.h"


int main() {
    Engine engine(800,600);

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
        sf::Vector2u(800.0f, 600.0f)
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

    auto wall1 = std::make_unique<StaticEntity>(
        false,
        sf::Vector2f(0, 300),
        sf::Vector2f(0.0f, 0.0f),
        sf::Vector2f(0.0f, 0.0f),
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        sf::Vector2f(640, 192)
    );
    std::vector<std::vector<int>> mat = {
        {0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1}
    };
    wall1->tileMap.loadTexture(0, "/home/navin/CLionProjects/Gengine/Assets/tileSet/png/Tiles/2.png");
    wall1->tileMap.loadTexture(1, "/home/navin/CLionProjects/Gengine/Assets/tileSet/png/Tiles/5.png");
    wall1->tileMap.loadTexture(2, "/home/navin/CLionProjects/Gengine/Assets/tileSet/png/Tiles/3.png");
    wall1->tileMap.setMatrix(mat);

    engine.addEntity(std::move(wall1));

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
        sf::Vector2f(64, 64)
    );
    std::vector<std::vector<int>> mat1 = {
        {0}
    };
    wall2->tileMap.loadTexture(0, "/home/navin/CLionProjects/Gengine/Assets/tileSet/png/Object/Crate.png");
    wall2->tileMap.setMatrix(mat1);

    wall2->addPhysics(EntityPhysics::applyGravity);

    engine.addEntity(std::move(wall2));

    engine.run();

    return 0;
}
