#pragma once

#include <thread>
#include <memory>

#include "GLManager/GLManager.hpp"
#include "Utility/Logger.hpp"
#include "GameDataStore/GameDataStore.hpp"

#include "GameClient.hpp"

class Game {
private:
    bool glManagerRunning = false;
    GLManager glManager;
    std::thread glManagerThread;

    Logger logger;

    std::shared_ptr<GameDataStore> gameState;
    std::shared_ptr<GameClient>    networkingClient;

    void _logicThread();
    std::thread logicThread;
public:
    Game();
    ~Game();

    // Start networking thread and rendering thread
    void startGame();
};