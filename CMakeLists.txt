cmake_minimum_required(VERSION 3.22.1)

project(ShooterGame VERSION 1.0 DESCRIPTION "A Shooter Game")

set(CMAKE_CXX_STANDARD 20)

include_directories(src/)

add_subdirectory(lib/LibGameNetworking)

file(GLOB_RECURSE GAME_SRC src/*.cpp)

add_executable(main ${GAME_SRC})

target_link_libraries(main fmt GL GLEW glfw GameNetworking)