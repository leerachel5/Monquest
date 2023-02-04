#include "BattleState.hpp"
#include "../WidgetManager.hpp"
#include "OverworldState.hpp"


BattleState::BattleState() : GameState(), dialogue{manager.getGroup(groupDialogue)}, party{manager.getGroup(groupParty)}, enemyParty{manager.getGroup(groupEnemyParty)}, player{nullptr}, enemy{nullptr} {}

BattleState::~BattleState() {}

void BattleState::enter() {
    Game::camera = camera;
    
    if (player == nullptr && enemy == nullptr) {
        player = OverworldState::player;
        enemy = OverworldState::enemy;
        
        for (std::string name : player->getComponent<PartyComponent>().party) {
            Entity* companion(&manager.addEntity());
            companion->addComponent<TransformComponent>(0, 0, 16, 12, 30);
            companion->addComponent<ProjectorComponent>(true);
            companion->addComponent<TextureComponent>(name);
            
            ProjectorComponent* projector = &companion->getComponent<ProjectorComponent>();
            projector->AddAnimation("back", 0, 1, 1);
            projector->AddAnimation("front", 1, 1, 1);
            projector->PlayAnimation("back");
            projector->setXToPercentOfWindow(6);
            projector->setYToPercentOfWindow(50);
            
            companion->addGroup(groupParty);
        }
        
        for (std::string name : enemy->getComponent<PartyComponent>().party) {
            Entity* monster(&manager.addEntity());
            monster->addComponent<TransformComponent>(0, 0, 16, 12, 20);
            monster->addComponent<ProjectorComponent>(true);
            monster->addComponent<TextureComponent>(name);
            
            ProjectorComponent* projector = &monster->getComponent<ProjectorComponent>();
            projector->AddAnimation("back", 0, 1, 1);
            projector->AddAnimation("front", 1, 1, 1);
            projector->PlayAnimation("front");
            projector->setXToPercentOfWindow(56);
            projector->setYToPercentOfWindow(10);
            
            monster->addGroup(groupEnemyParty);
        }
    }
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
    
    for (auto& e : enemyParty)
        e->draw();
    for (auto& p : party)
        p->draw();
    for (auto& d : dialogue)
        d->draw();
}
