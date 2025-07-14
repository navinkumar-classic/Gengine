
cmake_minimum_required(VERSION 3.14)
project(Gengine)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

add_executable(Gengine main.cpp)
target_link_libraries(Gengine sfml-graphics sfml-window sfml-system)