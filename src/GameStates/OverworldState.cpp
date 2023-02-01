#include "OverworldState.hpp"
#include "../Collision.hpp"
#include <sstream>


OverworldState::OverworldState() : GameState(), tiles{manager.getGroup(groupMap)}, mapLinks{manager.getGroup(groupMapLinks)},
    players{manager.getGroup(groupPlayers)}, colliders{manager.getGroup(groupColliders)}, tallGrass{manager.getGroup(groupTallGrass)}
{}

OverworldState::~OverworldState() {}

void OverworldState::enter() {
    isRunning  = true;
    Game::camera = camera;
}

void OverworldState::exit() {
    isRunning = false;
}

void OverworldState::init() {
    player = &manager.addEntity();
    playerPosLabel = &manager.addEntity();
    
    mapManager->init(manager, "map1", "terrain", "assets/map1.map", 25, 20, 2, 32);
    mapManager->addMap("map2", "terrain", "assets/map2.map", 25, 20, 2, 32);
    mapManager->addMap("map3", "terrain", "assets/map3.map", 50, 50, 2, 32);
    
    Map initialMap =  mapManager->getMap(mapManager->activeMap);
    camera = {0, 0, initialMap.sizeX * initialMap.tileSize, initialMap.sizeY * initialMap.tileSize};
    
    player->addComponent<TransformComponent>(1200.0f, 500.0f, 17, 23, 4);
    player->addComponent<SpriteComponent>("player", true);
    player->addComponent<KeyboardController>();
    player->addComponent<ColliderComponent>("player");
    player->addGroup(groupPlayers);
    
    SDL_Color white = {255, 255, 255, 255};
    playerPosLabel->addComponent<UILabel>(10, 10, "", "Arial", white);
}

void OverworldState::handleEvents(SDL_Event& event) {
    // event handler
}

void OverworldState::update() {
    TransformComponent playerTransform = player->getComponent<TransformComponent>();
    
    std::stringstream ss;
    ss << "Player position: " << playerTransform.position << std::endl;
    playerPosLabel->getComponent<UILabel>().SetLabelText(ss.str(), "Arial");
    
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
    
    playerPosLabel->draw();
}
