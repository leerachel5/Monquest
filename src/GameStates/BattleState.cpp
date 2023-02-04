#include "BattleState.hpp"
#include "../WidgetManager.hpp"


BattleState::BattleState() : GameState(), dialogue{manager.getGroup(groupDialogue)} {}

BattleState::~BattleState() {}

void BattleState::enter() {
    Game::camera = camera;
}

void BattleState::exit() {
}

void BattleState::init() {
    battlegroundTexture = Game::assets->GetTexture("battleground");
    
    SDL_Color textColor = { 0, 0, 0, 0 };
    
    std::vector<std::string> dialogue = {"Player has encountered a wild monster.", "You send your party to the fight."};
    
    Entity* dialogueBox = WidgetManager::CreateDialogueBox(&manager, 100, 55, 0, 0, 50, 14, 2, "dialogue box", dialogue, "Arial", 32, textColor);
    dialogueBox->getComponent<ProjectorComponent>().setXToPercentOfWindow(0);
    dialogueBox->getComponent<ProjectorComponent>().setYToPercentOfWindow(70);
    dialogueBox->getComponent<ProjectorComponent>().setWidthToPercentOfWindow(100);
    dialogueBox->getComponent<ProjectorComponent>().setHeightToPercentOfWindow(30);
    
    dialogueBox->addGroup(groupDialogue);
}

void BattleState::handleEvents(SDL_Event& event) {
    switch(event.type){
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    for (auto& d : dialogue) {
                        if (d->getComponent<ButtonComponent>().isHovering) {
                            TextComponent* text = &d->getComponent<TextComponent>();
                            if (text->isEmpty() || text->numberOfTexts() == 1)
                                d->destroy();
                            else {
                                text->removeCurrentText();
                            }
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

void BattleState::update() {
    manager.refresh();
    manager.update();
}

void BattleState::render() {
    TextureManager::Draw(battlegroundTexture, nullptr, nullptr);
    
    for (auto& d : dialogue)
        d->draw();
}
