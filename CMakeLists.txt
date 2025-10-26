
cmake_minimum_required(VERSION 3.14)
project(Gengine)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system audio)

add_executable(Gengine
        Engine/Scene/SceneType/GameScene.cpp
        Engine/Input/InputManager.cpp
        Engine/Entity/Entity.cpp
        Engine/Entity/EntityType/ControllableEntity.cpp
        Engine/Entity/EntityType/StaticEntity.cpp
        Engine/Physics/Collision/Collision.cpp
        Utility/Movement.cpp
        Utility/CollisionBehaviour.cpp
        Utility/EntityPhysics.cpp
        Utility/CameraBehaviour.cpp
        Engine/Sprite/SpriteManager/AnimatedSprite.cpp
        Engine/Sprite/SpriteManager/TileManager.cpp
        Engine/Entity/EntityType/AnimatedStaticEntity.cpp
        Engine/GameState/GameState.cpp
        Engine/UI/UIElement.cpp
        Engine/UI/UIElementType/TextUIElement.cpp
        Engine/Event/EventManager.cpp
        Engine/Engine.cpp
        Engine/Scene/Scene.cpp
        Engine/Scene/SceneType/MenuScene.cpp
        test_engine.cpp
        Engine/UI/UIElementType/ImageUIElement.cpp
        Engine/Music/MusicManager.cpp)
target_link_libraries(Gengine sfml-graphics sfml-window sfml-system sfml-audio)