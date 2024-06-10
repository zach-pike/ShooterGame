cmake_minimum_required(VERSION 3.22.1)

project(ShooterGame VERSION 1.0 DESCRIPTION "A Shooter Game")

set(CMAKE_CXX_STANDARD 20)

include_directories(src/)

add_subdirectory(lib/LibGameNetworking)

file(GLOB_RECURSE CLIENT_SRC src/Client/*.cpp)
file(GLOB_RECURSE SERVER_SRC src/Server/*.cpp)

file(GLOB_RECURSE UTIL_SRC src/Utility/*.cpp)
add_library(Utils STATIC ${UTIL_SRC})

add_executable(GameClient ${CLIENT_SRC})
add_executable(GameServer ${SERVER_SRC})

target_link_libraries(GameClient fmt GameNetworking Utils GL GLEW glfw )
target_link_libraries(GameServer fmt GameNetworking Utils)