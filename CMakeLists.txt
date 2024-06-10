cmake_minimum_required(VERSION 3.22.1)

project(ShooterGame VERSION 1.0 DESCRIPTION "A Shooter Game")

file(GLOB GAME_SRC src/*.cpp)

add_executable(main ${GAME_SRC})