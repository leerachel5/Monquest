#include "StateManager.hpp"


StateManager::StateManager() {}

StateManager::~StateManager() {}

void StateManager::addState(std::string stateID, GameState* state) {
    states.insert({stateID, state});
}

void StateManager::enterState(std::string stateID) {
    states.at(stateID)->enter();
}

void StateManager::exitState(std::string stateID) {
    states.at(stateID)->exit();
}

void StateManager::init() {
    for (std::pair<std::string, GameState*> kv : states) {
        kv.second->init();
    }
}

void StateManager::handleEvents(SDL_Event& event) {
    for (std::pair<std::string, GameState*> kv : states) {
        kv.second->handleEvents(event);
    }
}

void StateManager::update() {
    for (std::pair<std::string, GameState*> kv : states) {
        kv.second->update();
    }
}

void StateManager::render() {
    for (std::pair<std::string, GameState*> kv : states) {
        kv.second->render();
    }
}
