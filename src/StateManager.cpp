#include "StateManager.hpp"
#include "GameStates/GameStates.hpp"


const std::string StateManager::START_STATE = "overworld";
const std::string StateManager::DEFAULT_STATE = "main menu";

StateManager::StateManager() : activeState{StateManager::START_STATE} {}

StateManager::~StateManager() {}

void StateManager::addState(std::string stateID, GameState* state) {
    states.insert({stateID, state});
}

void StateManager::enterState(std::string stateID) {
    prevState = activeState;
    activeState = stateID;
    states.at(activeState)->enter();
}

void StateManager::exitState() {
    if (activeState != StateManager::DEFAULT_STATE) {
        prevState = activeState;
        activeState = StateManager::DEFAULT_STATE;
        states.at(activeState)->enter();
    }
}

bool StateManager::isRunning(std::string stateID) {
    return stateID == activeState;
}

void StateManager::init() {
    for (auto& p : states) {
        p.second->init();
    }
}

void StateManager::handleEvents(SDL_Event& event) {
    states.at(activeState)->handleEvents(event);
}

void StateManager::update() {
    states.at(activeState)->update();
}

void StateManager::render() {
    states.at(activeState)->render();
}
