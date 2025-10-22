
cmake_minimum_required(VERSION 3.14)
project(Gengine)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

add_executable(Gengine main.cpp
        Engine/Engine.cpp
        Engine/Input/Input.cpp
        Engine/Entity/Entity.cpp
        Engine/Entity/EntityType/ControllableEntity.cpp
        Engine/Entity/EntityType/StaticEntity.cpp
        Engine/Physics/Collision/Collision.cpp
        Util/Movement.cpp
        Util/CollisionBehaviour.cpp
        Util/EntityPhysics.cpp
        Util/CameraBehaviour.cpp
        Engine/Sprite/SpriteManager/AnimatedSprite.cpp
        Engine/Sprite/SpriteManager/TileManager.h
        Engine/Sprite/SpriteManager/TileManager.cpp
        Engine/Entity/EntityType/AnimatedStaticEntity.h
        Engine/Entity/EntityType/AnimatedStaticEntity.cpp
        Engine/GameState/GameState.h
        Engine/GameState/GameState.cpp
        Engine/UIElement/UIElement.h
        Engine/UIElement/UIElement.cpp
        Engine/UIElement/UIElementType/TextUIElement.h
        Engine/UIElement/UIElementType/TextUIElement.cpp)
target_link_libraries(Gengine sfml-graphics sfml-window sfml-system)