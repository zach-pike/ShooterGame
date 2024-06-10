#include "Game.hpp"

#include <functional>

#include "Common/PacketTypes.hpp"

void Game::_logicThread() {
    auto& messageQueue = networkingClient->getIncomingMessageQueue();

    while(glManagerRunning) {
        // Wait for a packet
        messageQueue.wait();

        // Decode a packet
        auto message = messageQueue.pop_front().message;

        switch((PacketType)message.header.id) {
            case PacketType::Heartbeat: {
                // Ping back with a heartbeat
                networkingClient->send(Message((std::uint32_t)PacketType::Heartbeat));
            } break;
        }
    }
}

Game::Game():
    logger("Game", Logger::FGColors::RED) {}
Game::~Game() {}

void Game::startGame() {
    // Create the datastore object
    gameState        = std::make_shared<GameDataStore>();

    // Connect to server
    networkingClient = std::make_shared<GameClient>();
    networkingClient->connectToServer("0.0.0.0", 8000);

    // Start the thread and wait for the manager thread to quit
    glManagerRunning = true;
    
    glManagerThread = std::thread([&]() { glManager.setup(); glManager.renderLoop(gameState); });
    logicThread     = std::thread(std::bind(&Game::_logicThread, this));

    glManagerThread.join();
    glManagerRunning = false;
    logicThread.join();

    // Disconnect from server
    networkingClient->disconnect();
}