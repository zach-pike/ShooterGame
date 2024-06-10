#pragma once

#include <thread>
#include <mutex>

#include <glm/glm.hpp>

// Thread safe
class GameDataStore {
private:
    glm::vec3 playerPos;
    std::mutex playerPosLock;
    
public:
    GameDataStore();
    ~GameDataStore();

    void setPlayerPos(glm::vec3 np);
    glm::vec3 getPlayerPos();
};