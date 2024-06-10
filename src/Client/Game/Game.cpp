#include "Game.hpp"

Game::Game():
    logger("Game", Logger::FGColors::RED) {}
Game::~Game() {}

void Game::startGame() {
    glManagerThread = std::thread([&]() { glManager.setup(); glManager.renderLoop(); });

    glManagerThread.join();
}