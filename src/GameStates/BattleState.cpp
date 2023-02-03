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
    
    layouts.push_back(createIntroTextBox());
    
    for (Layout<Widget*>* l : layouts)
        l->init();
}

void BattleState::handleEvents(SDL_Event& event) {
    for (Layout<Widget*>* l : layouts)
        l->handleEvents(event);
}

void BattleState::update() {
    for (Layout<Widget*>* l : layouts)
        l->update();
}

void BattleState::render() {
    TextureManager::Draw(battlegroundTexture, nullptr, nullptr);
    
    for (Layout<Widget*>* l : layouts)
        l->draw();
}
