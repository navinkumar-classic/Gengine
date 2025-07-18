
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
        Engine/PhysicsSystem/Collision/Collision.cpp
        Engine/GameInitializer/EntityInitializer.cpp
        Engine/Actions/Movement.cpp
        Engine/Actions/CollisionBehaviour.cpp
        Engine/PhysicsSystem/EntityPhysics/EntityPhysics.cpp)
target_link_libraries(Gengine sfml-graphics sfml-window sfml-system)