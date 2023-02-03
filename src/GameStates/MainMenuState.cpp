#include "MainMenuState.hpp"
#include "../StateManager.hpp"

extern StateManager states;

namespace {
    void enterOverworldState() {
        states.enterState("overworld");
        states.exitState("main menu");
    }

    int buttonW = 50;
    int buttonH = 14;
    int buttonSc = 8;
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
    
    // Group button widgets with grid layout
    GridLayout<Widget*>* menu = new GridLayout<Widget*>((Game::windowW - buttonW * buttonSc) / 2, (Game::windowH - buttonH * buttonSc) / 12, buttonW * buttonSc, Game::windowH - Game::windowH / 10, 6, 1);
    
    menu->addObject(continueButton, 0, 0);
    menu->addObject(saveButton, 1, 0);
    menu->addObject(loadButton, 2, 0);
    menu->addObject(settingsButton, 3, 0);
    menu->addObject(creditsButton, 4, 0);
    menu->addObject(quitButton, 5, 0);
    
    
    layouts.push_back(menu);
    
    for (Layout<Widget*>* l : layouts)
        l->init();
}

void MainMenuState::handleEvents(SDL_Event& event) {
    for (Layout<Widget*>* l : layouts)
        l->handleEvents(event);
}

void MainMenuState::update() {
    for (Layout<Widget*>* l : layouts)
        l->update();
}

void MainMenuState::render() {
    for (Layout<Widget*>* l : layouts)
        l->draw();
}
