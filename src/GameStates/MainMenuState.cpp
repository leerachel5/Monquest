#include "MainMenuState.hpp"
#include "../Widgets/Button.hpp"
#include "../StateManager.hpp"


extern StateManager states;

namespace {
    void enterOverworldState() {
        states.enterState("overworld");
        states.exitState("main menu");
    }

    int buttonW = 50;
    int buttonH = 14;
    int buttonSc = 6;
    SDL_Color buttonTextColor = { 255,255,255,255 };
}


MainMenuState::MainMenuState() : GameState() {}

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
    Button* continueButton = new Button((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) / 12, buttonW, buttonH, buttonSc, enterOverworldState, "Continue", "button", "Arial", buttonTextColor);
    Button* saveButton = new Button((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) / 4, buttonW, buttonH, buttonSc, [](){}, "Save", "button", "Arial", buttonTextColor);
    Button* loadButton = new Button((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) * 5/12, buttonW, buttonH, buttonSc, [](){}, "Load", "button", "Arial", buttonTextColor);
    Button* settingsButton = new Button((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) * 7/12, buttonW, buttonH, buttonSc, [](){}, "Settings", "button", "Arial", buttonTextColor);
    Button* creditsButton = new Button((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) * 3/4, buttonW, buttonH, buttonSc, [](){}, "Credits", "button", "Arial", buttonTextColor);
    Button* quitButton = new Button((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) * 11/12, buttonW, buttonH, buttonSc, []() { Game::isRunning = false; }, "Quit", "button", "Arial", buttonTextColor);
    
    widgets.push_back(continueButton);
    widgets.push_back(saveButton);
    widgets.push_back(loadButton);
    widgets.push_back(settingsButton);
    widgets.push_back(creditsButton);
    widgets.push_back(quitButton);
    
    for (Widget* w : widgets)
        w->init();
}

void MainMenuState::handleEvents(SDL_Event& event) {
    for (Widget* w : widgets)
        w->handleEvents(event);
}

void MainMenuState::update() {
    SDL_SetRenderDrawColor(Game::renderer, 95, 97, 103, 0);
    
    for (Widget* w : widgets)
        w->update();
}

void MainMenuState::render() {
    for (Widget* w : widgets)
        w->draw();
}
