#include "BattleState.hpp"
#include "../WidgetManager.hpp"


BattleState::BattleState() : GameState(), widgets{manager.getGroup(groupWidgets)} {}

BattleState::~BattleState() {}

void BattleState::enter() {
    Game::camera = camera;
}

void BattleState::exit() {
}

void BattleState::init() {
    battlegroundTexture = Game::assets->GetTexture("battleground");
    
    SDL_Color textColor = { 0, 0, 0, 0 };
    
    Entity* textBox = WidgetManager::CreateTextBox(&manager, 100, 55, 0, 0, 50, 14, 2, "dialogue box", "Player has encountered a wild monster.", "Arial", 32, textColor);
    textBox->getComponent<ProjectorComponent>().setXToPercentOfWindow(0);
    textBox->getComponent<ProjectorComponent>().setYToPercentOfWindow(70);
    textBox->getComponent<ProjectorComponent>().setWidthToPercentOfWindow(100);
    textBox->getComponent<ProjectorComponent>().setHeightToPercentOfWindow(30);
    
    textBox->addGroup(groupWidgets);
}

void BattleState::handleEvents(SDL_Event& event) {
}

void BattleState::update() {
    manager.refresh();
    manager.update();
}

void BattleState::render() {
    TextureManager::Draw(battlegroundTexture, nullptr, nullptr);
    
    for (auto& w : widgets)
        w->draw();
}
