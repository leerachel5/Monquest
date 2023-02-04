#include "BattleState.hpp"
#include "../WidgetManager.hpp"
#include "OverworldState.hpp"


BattleState::BattleState() : GameState(), introDialogue{manager.getGroup(groupIntroDialogue)}, battleWidgets{manager.getGroup(groupBattleWidgets)}, party{manager.getGroup(groupParty)}, enemyParty{manager.getGroup(groupEnemyParty)}, player{nullptr}, enemy{nullptr} {}

BattleState::~BattleState() {}

void BattleState::enter() {
    Game::camera = camera;
    
    if (player == nullptr && enemy == nullptr) {
        player = OverworldState::player;
        enemy = OverworldState::enemy;
        
        for (Creature c : player->getComponent<PartyComponent>().creatures) {
            Entity* companion(&manager.addEntity());
            companion->addComponent<TransformComponent>(0, 0, 16, 12, 30);
            companion->addComponent<ProjectorComponent>(true);
            companion->addComponent<TextureComponent>(c.name);
            
            ProjectorComponent* projector = &companion->getComponent<ProjectorComponent>();
            projector->AddAnimation("back", 0, 1, 1);
            projector->AddAnimation("front", 1, 1, 1);
            projector->PlayAnimation("back");
            projector->setXToPercentOfWindow(6);
            projector->setYToPercentOfWindow(50);
            
            companion->addGroup(groupParty);
        }
        
        for (Creature c : enemy->getComponent<PartyComponent>().creatures) {
            Entity* monster(&manager.addEntity());
            monster->addComponent<TransformComponent>(0, 0, 16, 12, 20);
            monster->addComponent<ProjectorComponent>(true);
            monster->addComponent<TextureComponent>(c.name);
            
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
    dialogueBox->addGroup(groupIntroDialogue);
}

void BattleState::handleEvents(SDL_Event& event) {
    switch(event.type){
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    for (auto& d : introDialogue) {
                        if (d->getComponent<ButtonComponent>().isHovering) {
                            TextComponent* text = &d->getComponent<TextComponent>();
                            if (text->isEmpty() || text->numberOfTexts() == 1) {
                                d->destroy();
                                
                                Entity* enemyStatusBar = WidgetManager::CreateImageBox(&manager, 0, 0, 100, 32, 4, "status bar");
                                enemyStatusBar->getComponent<ProjectorComponent>().setWidthToPercentOfWindow(45);
                                enemyStatusBar->getComponent<ProjectorComponent>().setHeightToPercentOfWindow(20);
                                enemyStatusBar->addGroup(groupBattleWidgets);
                                
                                Entity* playerStatusBar = WidgetManager::CreateImageBox(&manager, 0, 0, 100, 32, 4, "status bar");
                                playerStatusBar->getComponent<ProjectorComponent>().setXToPercentOfWindow(55);
                                playerStatusBar->getComponent<ProjectorComponent>().setYToPercentOfWindow(80);
                                playerStatusBar->getComponent<ProjectorComponent>().setWidthToPercentOfWindow(45);
                                playerStatusBar->getComponent<ProjectorComponent>().setHeightToPercentOfWindow(20);
                                playerStatusBar->addGroup(groupBattleWidgets);

                                break;
                            }
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
    for(auto& bw : battleWidgets)
        bw->draw();
    for (auto& d : introDialogue)
        d->draw();
}
