#include "BattleState.hpp"

namespace {
    int introTextBoxW = 50;
    int introTextBoxH = 14;
    int introBoxTextSize = 32;
    SDL_Color introBoxTextColor = { 0,0,0,0 };

    GridLayout<Widget*>* createIntroTextBox() {
        Button* introTextBox = new Button(0, 0, introTextBoxW, introTextBoxH, 0, "dialogue box", "Player has encountered a wild monster.", "Arial", introBoxTextSize, introBoxTextColor, []() {}, true);
        
        GridLayout<Widget*>* introTextGrid = new GridLayout<Widget*>(1, 1);
        introTextGrid->setYToPercentOfWindow(70);
        introTextGrid->setWidthToPercentOfWindow(100);
        introTextGrid->setHeightToPercentOfWindow(30);
        
        introTextGrid->addObject(introTextBox, 0, 0);
        
        return introTextGrid;
    }
}

BattleState::BattleState() : GameState() {}

BattleState::~BattleState() {}

void BattleState::enter() {
    Game::camera = camera;
}

void BattleState::exit() {
}

void BattleState::init() {
    battlegroundTexture = Game::assets->GetTexture("battleground");
    
    layouts.emplace("intro text box", createIntroTextBox());
    
    for (auto& p : layouts)
        p.second->init();
}

void BattleState::handleEvents(SDL_Event& event) {
    for (auto& p : layouts)
        p.second->handleEvents(event);
}

void BattleState::update() {
    for (auto& p : layouts)
        p.second->update();
}

void BattleState::render() {
    TextureManager::Draw(battlegroundTexture, nullptr, nullptr);
    
    for (auto& p : layouts)
        p.second->draw();
}
