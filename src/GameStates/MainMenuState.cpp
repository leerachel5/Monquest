#include "MainMenuState.hpp"
#include "../StateManager.hpp"

extern StateManager states;


MainMenuState::MainMenuState() : GameState(), buttons{manager.getGroup(Game::groupButtons)} {}

MainMenuState::~MainMenuState() {}

void MainMenuState::enter() {
    isRunning  = true;
    Game::camera = camera;
}

void MainMenuState::exit() {
    isRunning = false;
}

void MainMenuState::init() {
    Entity* mondexButton = &manager.addEntity();
    int buttonW = 144;
    int buttonH = 48;
    mondexButton->addComponent<TransformComponent>(Game::windowW/2 - buttonW, Game::windowH/2 - buttonH, 144, 48, 2);
    mondexButton->addComponent<SpriteComponent>("start_button", false);
    mondexButton->addComponent<ButtonComponent>();
    mondexButton->addGroup(Game::groupButtons);
}
void MainMenuState::handleEvents(SDL_Event& event) {
    switch(event.type){
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    for (auto& b : manager.getGroup(Game::groupButtons)) {
                        if (b->getComponent<ButtonComponent>().isHovering) {
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
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 255, 0);
    manager.refresh();
    manager.update();
}
void MainMenuState::render() {
    for (auto& b : buttons)
        b->draw();
}
