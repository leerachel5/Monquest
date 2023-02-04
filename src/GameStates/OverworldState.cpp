#include "OverworldState.hpp"
#include "../Collision.hpp"
#include "../StateManager.hpp"
#include <sstream>

extern StateManager states;

Entity* OverworldState::player;
Entity* OverworldState::enemy;

namespace {
    const float TRIGGER_BATTLE_PERCENTAGE = 0.1;
    int randModDivisor = 100 / TRIGGER_BATTLE_PERCENTAGE;
}


OverworldState::OverworldState() : GameState(), tiles{manager.getGroup(groupMap)}, mapLinks{manager.getGroup(groupMapLinks)},
    players{manager.getGroup(groupPlayers)}, colliders{manager.getGroup(groupColliders)}, tallGrass{manager.getGroup(groupTallGrass)}
{}

OverworldState::~OverworldState() {}

void OverworldState::enter() {
    Game::camera = camera;
}

void OverworldState::exit() {
}

void OverworldState::init() {
    mapManager->init(manager, "map1", "terrain", "assets/map1.map", 25, 20, 2, 32);
    mapManager->addMap("map2", "terrain", "assets/map2.map", 25, 20, 2, 32);
    mapManager->addMap("map3", "terrain", "assets/map3.map", 50, 50, 2, 32);
    
    Map initialMap =  mapManager->getMap(mapManager->activeMap);
    camera = {0, 0, initialMap.sizeX * initialMap.tileSize, initialMap.sizeY * initialMap.tileSize};
    
    player = &manager.addEntity();
    player->addComponent<TransformComponent>(1200.0f, 500.0f, 17, 23, 4);
    player->addComponent<ProjectorComponent>(true);
    player->addComponent<TextureComponent>("player");
    player->addComponent<SpriteComponent>();
    player->addComponent<KeyboardController>();
    player->addComponent<ColliderComponent>("player");
    
    std::vector<std::string> party = {"red slime"};
    player->addComponent<PartyComponent>(party);
    
    player->addGroup(groupPlayers);
}

void OverworldState::handleEvents(SDL_Event& event) {
    // event handler
}

void OverworldState::update() {
    TransformComponent playerTransform = player->getComponent<TransformComponent>();
    
    manager.refresh();
    manager.update();
    
    for (auto& l : mapLinks) {
        if (Collision::AABB(player->getComponent<ColliderComponent>().collider, l->getComponent<ColliderComponent>().collider)) {
            LinkComponent link = l->getComponent<LinkComponent>();
            mapManager->loadMap(manager, link.destMap);
            
            Map destMap = mapManager->getMap(link.destMap);
            camera.w = destMap.sizeX * destMap.tileSize;
            camera.h = destMap.sizeY * destMap.tileSize;
            
            player->getComponent<TransformComponent>().position.x = link.destX;
            player->getComponent<TransformComponent>().position.y = link.destY;
        }
    }
    
    camera.x = player->getComponent<TransformComponent>().position.x - Game::windowW / 2;
    camera.y = player->getComponent<TransformComponent>().position.y - Game::windowH / 2;
    
    Map activeMap = mapManager->getMap(mapManager->activeMap);
    
    if (camera.x < 0)
        camera.x = 0;
    if (camera.y < 0)
        camera.y = 0;
    if (camera.x > camera.w * activeMap.mapScale - Game::windowW)
        camera.x = camera.w * activeMap.mapScale - Game::windowW;
    if (camera.y > camera.h * activeMap.mapScale - Game::windowH)
        camera.y = camera.h * activeMap.mapScale - Game::windowH;
    
    Game::camera = camera;
    
    // Walking in tall grass has a chance to send player to battle state
    if (player->getComponent<TransformComponent>().velocity.x != 0 || player->getComponent<TransformComponent>().velocity.y != 0) {
        if (std::rand() % randModDivisor == 0) {
            for (auto& tg : manager.getGroup(groupTallGrass)) {
                TileComponent tgTile = tg->getComponent<TileComponent>();
                SDL_Rect tgCol = { static_cast<int>(tgTile.position.x), static_cast<int>(tgTile.position.y), tgTile.destRect.w, tgTile.destRect.h };
                if (Collision::AABB(player->getComponent<ColliderComponent>().collider, tgCol)) {
                    OverworldState::player = player;
                    OverworldState::enemy = player;
                    states.enterState("battle");
                    break;
                }
            }
        }
    }
}

void OverworldState::render() {
    for (auto& t : tiles)
        t->draw();
    for (auto& g : tallGrass)
        g->draw();
//    for (auto& c : colliders)
//        c->draw();
    for (auto& p : players)
        p->draw();
}
