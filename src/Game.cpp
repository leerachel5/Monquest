#include "Game.hpp"
#include "MapManager.hpp"
#include "ECS/Components.hpp"
#include "Collision.hpp"
#include <sstream>

MapManager* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = {0,0,800,640};

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& playerPosLabel(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char *title, int xpos, int ypos, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
        
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        
        isRunning = true;
    } else {
        isRunning = false;
    }
    if (TTF_Init() == -1) {
        std::cout << "Error: SDL_TTF failed to initialize" << std::endl;
        exit(1);
    }
    assets->AddTexture("terrain", "assets/terrain_ss.png");
    assets->AddTexture("player", "assets/player.png");
    
    assets->AddFont("Arial", "assets/Arial.ttf", 16);
    
    map = new MapManager();
    map->init("map1", "terrain", "assets/map1.map", 25, 20, 2, 32);
    map->addMap("map2", "terrain", "assets/map2.map", 25, 20, 2, 32);
    
    player.addComponent<TransformComponent>(1150.0f, 500.0f, 23, 17, 4);
    player.addComponent<SpriteComponent>("player", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);
    
    SDL_Color white = {255, 255, 255, 255};
    playerPosLabel.addComponent<UILabel>(10, 10, "", "Arial", white);
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& mapLinks(manager.getGroup(Game::groupMapLinks));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

void Game::handleEvents() {
    SDL_PollEvent(&event);

    switch(event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_m:
                    if (map->activeMap == "map1")
                        map->loadMap("map2");
                    else
                        map->loadMap("map1");
                    break;
                default:
                    break;
            }
            break;
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

void Game::update() {
    TransformComponent playerTransform = player.getComponent<TransformComponent>();
    
    std::stringstream ss;
    ss << "Player position: " << playerTransform.position << std::endl;
    playerPosLabel.getComponent<UILabel>().SetLabelText(ss.str(), "Arial");
    
    manager.refresh();
    manager.update();
    
    for (auto& l : mapLinks) {
        if (Collision::AABB(player.getComponent<ColliderComponent>().collider, l->getComponent<ColliderComponent>().collider)) {
            map->loadMap(l->getComponent<LinkComponent>().destMap);
            player.getComponent<TransformComponent>().position.x = l->getComponent<LinkComponent>().destX;
            player.getComponent<TransformComponent>().position.y = l->getComponent<LinkComponent>().destY;
        }
    }
    
    camera.x = player.getComponent<TransformComponent>().position.x - 400;
    camera.y = player.getComponent<TransformComponent>().position.y - 320;
    
    if (camera.x < 0)
        camera.x = 0;
    if (camera.y < 0)
        camera.y = 0;
    if (camera.x > camera.w)
        camera.x = camera.w;
    if (camera.y > camera.h)
        camera.y = camera.h;
}

void Game::render() {
    SDL_RenderClear(renderer);
    
    for (auto& t : tiles)
        t->draw();
    for (auto& c : colliders)
        c->draw();
    for (auto& p : players)
        p->draw();
    
    playerPosLabel.draw();
    
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
