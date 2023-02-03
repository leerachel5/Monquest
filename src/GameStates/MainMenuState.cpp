#include "MainMenuState.hpp"
#include "../StateManager.hpp"

extern StateManager states;

namespace {
    int buttonW = 50;
    int buttonH = 14;
    int buttonSc = 8;
    int buttonTextSize = 60;
    SDL_Color buttonTextColor = { 255,255,255,255 };

    void resumePausedState() {
        if (states.prevState != "")
            states.enterState(states.prevState);
        else // At start, resume start state
            states.enterState(StateManager::START_STATE);
    }

    GridLayout<Widget*>* createMenuLayout() {
        // Create 6 buttons: Continue, Save, Load, Settings, Credits, and Quit
        Button* continueButton = new Button((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) / 12, buttonW, buttonH, buttonSc, "button", "Continue", "Arial", buttonTextSize, buttonTextColor, resumePausedState, true);
        Button* saveButton = new Button((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) / 4, buttonW, buttonH, buttonSc, "button", "Save", "Arial", buttonTextSize, buttonTextColor, [](){}, true);
        Button* loadButton = new Button((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) * 5/12, buttonW, buttonH, buttonSc, "button", "Load", "Arial", buttonTextSize, buttonTextColor, [](){}, true);
        Button* settingsButton = new Button((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) * 7/12, buttonW, buttonH, buttonSc, "button", "Settings", "Arial", buttonTextSize, buttonTextColor, [](){}, true);
        Button* creditsButton = new Button((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) * 3/4, buttonW, buttonH, buttonSc, "button", "Credits", "Arial", buttonTextSize, buttonTextColor, [](){}, true);
        Button* quitButton = new Button((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) * 11/12, buttonW, buttonH, buttonSc, "button", "Quit", "Arial", buttonTextSize, buttonTextColor, []() { Game::isRunning = false; }, true);
        
        // Group button widgets with grid layout
        GridLayout<Widget*>* menu = new GridLayout<Widget*>((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) / 12, buttonW * buttonSc, Game::windowH - Game::windowH / 10, 6, 1);
        menu->addObject(continueButton, 0, 0);
        menu->addObject(saveButton, 1, 0);
        menu->addObject(loadButton, 2, 0);
        menu->addObject(settingsButton, 3, 0);
        menu->addObject(creditsButton, 4, 0);
        menu->addObject(quitButton, 5, 0);
        
        return menu;
    }
}


MainMenuState::MainMenuState() : GameState() {}

MainMenuState::~MainMenuState() {}

void MainMenuState::enter() {
    Game::camera = camera;
}

void MainMenuState::exit() {
}

void MainMenuState::init() {
    layouts.emplace("menu buttons", createMenuLayout());
    
    for (auto& p : layouts)
        p.second->init();
}

void MainMenuState::handleEvents(SDL_Event& event) {
    for (auto& p : layouts)
        p.second->handleEvents(event);
}

void MainMenuState::update() {
    for (auto& p : layouts)
        p.second->update();
}

void MainMenuState::render() {
    for (auto& p : layouts)
        p.second->draw();
}
