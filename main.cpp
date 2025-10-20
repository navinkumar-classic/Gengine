
#include <functional>
#include <sstream>
#include <iomanip>
#include "Engine/Entity/EntityType/ControllableEntity.h"
#include "Engine/Entity/EntityType/StaticEntity.h"
#include "Util/Movement.h"
#include "Engine/Engine.h"
#include "Util/CollisionBehaviour.h"
#include "Util/EntityPhysics.h"
#include "Engine/Camera/CameraBehaviour.h"

std::unordered_map<int, std::string> ref_texture = {
    {64, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Boxes/4.png"},
    {71, "/home/navin/CLionProjects/Gengine/Assets/swamp/Objects/Trees/1.png"}
};

int main() {
    std::string basePath = "/home/navin/CLionProjects/Gengine/Assets/swamp/Tiles/Tile_";

    for (int i = 1; i <= 60; ++i) {
        std::ostringstream oss;
        oss << basePath << std::setw(2) << std::setfill('0') << i << ".png";
        ref_texture[i] = oss.str();
    }

    Engine engine(1200,800);

    engine.setFrameRate(120);
    engine.setBackgroundTexture("/home/navin/CLionProjects/Gengine/Assets/swamp/Background/Background.png");

    engine.bindAction("RIGHT",sf::Keyboard::D);
    engine.bindAction("LEFT",sf::Keyboard::A);
    engine.bindAction("UP",sf::Keyboard::Space);

    engine.addEntity(std::move(
        std::make_unique<StaticEntity>(
            sf::Vector2f(0, 600),
            sf::Vector2f(80, 80),
            std::vector<std::vector<int>>{
                {1,2,2,2,2,2,2,2,2,3},
                {11,12,12,12,12,12,12,12,12,13},
                {11,12,12,12,12,12,12,12,12,13}
                },"ground", ref_texture
            )
    ));

    engine.addEntity(std::move(
        std::make_unique<StaticEntity>(
            sf::Vector2f(900, 400),
            sf::Vector2f(80, 80),
            std::vector<std::vector<int>>{
            {1,2,2,2,2,2,2,2,2,3},
            {11,12,12,12,12,12,12,12,12,13},
            {21,22,22,22,22,22,22,22,22,23}
            },"ground",ref_texture
        )
    ));

    engine.addEntity(std::move(
        std::make_unique<StaticEntity>(
            sf::Vector2f(400, 394),
            sf::Vector2f(202, 206),
            std::vector<std::vector<int>>{
            {71}
            },"tree",ref_texture
        )
    ));

    engine.addEntity(std::move(
        std::make_unique<StaticEntity>(
            sf::Vector2f(860, 750),
            sf::Vector2f(80, 80),
            std::vector<std::vector<int>>{
                {32,33,33,33,33,33,33,33,33,34}
            },"ground", ref_texture
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

    player->Sprite.addTexture("DEFAULT","/home/navin/CLionProjects/Gengine/Assets/pinkMonster/Pink_Monster_Idle_4.png",4 );
    player->Sprite.addTexture("WALK","/home/navin/CLionProjects/Gengine/Assets/pinkMonster/Pink_Monster_Walk_6.png",6 );
    player->Sprite.addTexture("JUMP","/home/navin/CLionProjects/Gengine/Assets/pinkMonster/Pink_Monster_Jump_8.png",8 );

    player->addPhysics(EntityPhysics::applyGravity);
    player->addPhysics([](Entity& entity, Input& input, float dt){EntityPhysics::applyDeacceleration(entity, input, dt, "RIGHT", "LEFT");});

    engine.addEntity(std::move(player));

    auto crate1 = std::make_unique<StaticEntity>(
        true,
        sf::Vector2f(500, 0),
        sf::Vector2f(0.0f, 0.0f),
        sf::Vector2f(0.0f, 1100.0f),
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        sf::Vector2f(66, 52),
        std::vector<std::vector<int>>{
            {64}
        },
        "crate",
        ref_texture
    );
    crate1->addPhysics(EntityPhysics::applyGravity);

    engine.addEntity(std::move(crate1));

    engine.addEntryToCollisionHandler("pink_monster", "ground", CollisionBehaviour::ControllableToStaticCollision);
    engine.addEntryToCollisionHandler("pink_monster", "crate", CollisionBehaviour::ControllableToStaticCollision);
    engine.addEntryToCollisionHandler("crate", "ground", CollisionBehaviour::ControllableToStaticCollision);

    engine.addCameraBehaviour([](Entity& player, sf::View& camera){ cameraBehaviour::cameraTracking(player, camera, 200.0f, 2000.0f); }, 4);

    engine.run();

    return 0;
}
