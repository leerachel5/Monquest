#include "OverworldState.hpp"
#include "../Collision.hpp"
#include <sstream>


OverworldState::OverworldState() : GameState(), tiles{manager.getGroup(Game::groupMap)}, mapLinks{manager.getGroup(Game::groupMapLinks)},
    players{manager.getGroup(Game::groupPlayers)}, colliders{manager.getGroup(Game::groupColliders)}
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
    camera = {0, 0, 800, 640};
    player = &manager.addEntity();
    playerPosLabel = &manager.addEntity();
    
    mapManager->init(&manager, "map1", "terrain", "assets/map1.map", 25, 20, 2, 32);
    mapManager->addMap("map2", "terrain", "assets/map2.map", 25, 20, 2, 32);
    
    player->addComponent<TransformComponent>(1200.0f, 500.0f, 23, 17, 4);
    player->addComponent<SpriteComponent>("player", true);
    player->addComponent<KeyboardController>();
    player->addComponent<ColliderComponent>("player");
    player->addGroup(Game::groupPlayers);
    
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
            mapManager->loadMap(&manager, l->getComponent<LinkComponent>().destMap);
            player->getComponent<TransformComponent>().position.x = l->getComponent<LinkComponent>().destX;
            player->getComponent<TransformComponent>().position.y = l->getComponent<LinkComponent>().destY;
        }
    }
    
    Game::camera.x = player->getComponent<TransformComponent>().position.x - 400;
    Game::camera.y = player->getComponent<TransformComponent>().position.y - 320;
    
    if (Game::camera.x < 0)
        Game::camera.x = 0;
    if (Game::camera.y < 0)
        Game::camera.y = 0;
    if (Game::camera.x > Game::camera.w)
        Game::camera.x = Game::camera.w;
    if (Game::camera.y > Game::camera.h)
        Game::camera.y = Game::camera.h;
}

void OverworldState::render() {
    for (auto& t : tiles)
        t->draw();
    //    for (auto& c : colliders)
    //        c->draw();
    for (auto& p : players)
        p->draw();
    
    playerPosLabel->draw();
}
