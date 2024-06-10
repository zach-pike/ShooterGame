#pragma once

#include <thread>

#include "GLManager/GLManager.hpp"
#include "Utility/Logger.hpp"

class Game {
private:
    GLManager glManager;
    std::thread glManagerThread;

    Logger logger;
public:
    Game();
    ~Game();

    // Start networking thread and rendering thread
    void startGame();
};