#include "BattleState.hpp"

BattleState::BattleState() : GameState() {}

BattleState::~BattleState() {}

void BattleState::enter() {
    isRunning  = true;
    Game::camera = camera;
}

void BattleState::exit() {
    isRunning = false;
}

void BattleState::init() {
    battlegroundTexture = Game::assets->GetTexture("battleground");
}

void BattleState::handleEvents(SDL_Event& event) {}

void BattleState::update() {}

void BattleState::render() {
    TextureManager::Draw(battlegroundTexture, nullptr, nullptr);
}
