#include "MainMenuState.hpp"
#include "../StateManager.hpp"
#include "../Widgets/Button.hpp"

extern StateManager states;


MainMenuState::MainMenuState() : GameState(), buttons{manager.getGroup(groupButtons)} {}

MainMenuState::~MainMenuState() {}

void MainMenuState::enter() {
    isRunning  = true;
    Game::camera = camera;
}

void MainMenuState::exit() {
    isRunning = false;
}

void MainMenuState::init() {
    // Initialize 6 buttons: Continue, Save, Load, Settings, Credits, and Quit
    Button continueButton(&manager);
    Button saveButton(&manager);
    Button loadButton(&manager);
    Button settingsButton(&manager);
    Button creditsButton(&manager);
    Button quitButton(&manager);
    
    int buttonW = 50;
    int buttonH = 14;
    int buttonSc = 6;
    SDL_Color buttonTextColor = { 255,255,255,255 };
    
    continueButton.createButton((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) / 12, buttonW, buttonH, buttonSc, "Continue", "Arial", buttonTextColor);
    saveButton.createButton((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) / 4, buttonW, buttonH, buttonSc, "Save", "Arial", buttonTextColor);
    loadButton.createButton((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) * 5/12, buttonW, buttonH, buttonSc, "Load", "Arial", buttonTextColor);
    settingsButton.createButton((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) * 7/12, buttonW, buttonH, buttonSc, "Settings", "Arial", buttonTextColor);
    creditsButton.createButton((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) * 3/4, buttonW, buttonH, buttonSc, "Credits", "Arial", buttonTextColor);
    quitButton.createButton((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) * 11/12, buttonW, buttonH, buttonSc, "Quit", "Arial", buttonTextColor);
}
void MainMenuState::handleEvents(SDL_Event& event) {
    switch(event.type){
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    for (auto& b : manager.getGroup(groupButtons)) {
                        if (b->getComponent<MouseController>().isHovering) {
                            states.enterState("overworld");
                            states.exitState("main menu");
                        }
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
    SDL_SetRenderDrawColor(Game::renderer, 95, 97, 103, 0);
    manager.refresh();
    manager.update();
}
void MainMenuState::render() {
    for (auto& b : buttons)
        b->draw();
}
