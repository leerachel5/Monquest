#include "MainMenuState.hpp"
#include "../StateManager.hpp"
#include "../WidgetManager.hpp"

extern StateManager states;

namespace {
    void resumePausedState() {
        if (states.prevState != "")
            states.enterState(states.prevState);
        else // At start, resume start state
            states.enterState(StateManager::START_STATE);
    }
}

MainMenuState::MainMenuState() : GameState(), buttons{manager.getGroup(groupButtons)} {}

MainMenuState::~MainMenuState() {}

void MainMenuState::enter() {
    Game::camera = camera;
}

void MainMenuState::exit() {
}

void MainMenuState::init() {
    int buttonXOffset = 75;
    int buttonYOffset = 28;
    int buttonW = 50;
    int buttonH = 14;
    int buttonSc = 8;
    int buttonTextSize = 50;
    SDL_Color textColor = { 255, 255, 255, 255 };
    
    Entity* continueButton = WidgetManager::CreateButton(&manager, buttonXOffset, buttonYOffset, (Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) / 12, buttonW, buttonH, buttonSc, "button", "Continue", "Arial", buttonTextSize, textColor, resumePausedState);
    Entity* saveButton = WidgetManager::CreateButton(&manager, buttonXOffset, buttonYOffset, (Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) / 4, buttonW, buttonH, buttonSc, "button", "Save", "Arial", buttonTextSize, textColor, [](){});
    Entity* loadButton = WidgetManager::CreateButton(&manager, buttonXOffset, buttonYOffset, (Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) * 5/12, buttonW, buttonH, buttonSc, "button", "Load", "Arial", buttonTextSize, textColor, [](){});
    Entity* settingsButton = WidgetManager::CreateButton(&manager, buttonXOffset, buttonYOffset, (Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) * 7/12, buttonW, buttonH, buttonSc, "button", "Settings", "Arial", buttonTextSize, textColor, [](){});
    Entity* creditsButton = WidgetManager::CreateButton(&manager, buttonXOffset, buttonYOffset, (Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) * 3/4, buttonW, buttonH, buttonSc, "button", "Credits", "Arial", buttonTextSize, textColor, [](){});
    Entity* quitButton = WidgetManager::CreateButton(&manager, buttonXOffset, buttonYOffset, (Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) * 11/12, buttonW, buttonH, buttonSc, "button", "Quit", "Arial", buttonTextSize, textColor, [](){Game::isRunning = false;});
    
    continueButton->addGroup(groupButtons);
    saveButton->addGroup(groupButtons);
    loadButton->addGroup(groupButtons);
    settingsButton->addGroup(groupButtons);
    creditsButton->addGroup(groupButtons);
    quitButton->addGroup(groupButtons);
}

void MainMenuState::handleEvents(SDL_Event& event) {
    switch(event.type){
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    for (auto& b : buttons) {
                        ButtonComponent button = b->getComponent<ButtonComponent>();
                        if (button.isHovering)
                            button.func();
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void MainMenuState::update() {
    manager.refresh();
    manager.update();
}

void MainMenuState::render() {
    for (auto& b : buttons)
        b->draw();
}
