#include "Game.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Collision.hpp"
#include <sstream>

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = {0,0,800,640};

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& playerPosLabel(manager.addEntity());
auto& colliderPosLabel(manager.addEntity());

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
    assets->AddTexture("projectile", "assets/projectile.png");
    
    assets->AddFont("Arial", "assets/Arial.ttf", 16);
    
    map = new Map("terrain", 2, 32);
    
    map->LoadMap("assets/map.map", 25, 20);
    
    player.addComponent<TransformComponent>(800.0f, 640.0f, 23, 17, 4);
    player.addComponent<SpriteComponent>("player", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);
    
    SDL_Color white = {255, 255, 255, 255};
    playerPosLabel.addComponent<UILabel>(10, 10, "", "Arial", white);
    colliderPosLabel.addComponent<UILabel>(250, 10, "", "Arial", white);
    
    assets->CreateProjectile(Vector2D(600.0f, 600.0f), Vector2D(1.0f, 0.0f), 250, 1, "projectile");
    assets->CreateProjectile(Vector2D(500.0f, 600.0f), Vector2D(1.0f, -0.5f), 250, 1, "projectile");
    assets->CreateProjectile(Vector2D(400.0f, 600.0f), Vector2D(1.0f, 1.0f), 250, 1, "projectile");
    assets->CreateProjectile(Vector2D(600.0f, 600.0f), Vector2D(1.0f, -1.0f), 250, 1, "projectile");
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

void Game::handleEvents() {
    SDL_PollEvent(&event);

    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

void Game::update() {
    SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
    TransformComponent playerTransform = player.getComponent<TransformComponent>();
    
    std::stringstream ss;
    ss << "Player position: " << playerTransform.position << std::endl;
    playerPosLabel.getComponent<UILabel>().SetLabelText(ss.str(), "Arial");
    
    manager.refresh();
    manager.update();
    
    for (auto& c : colliders) {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        Collision::Direction direction;
        
        if (Collision::AABB(playerCol, cCol, direction)) {
            if (direction.N && playerTransform.position.y - playerTransform.velocity.y * playerTransform.speed >= cCol.y + cCol.h)
                player.getComponent<TransformComponent>().position.y = cCol.y + cCol.h + 1;
            else if (direction.S && playerTransform.position.y + (playerTransform.height * playerTransform.scale) - (playerTransform.velocity.y * playerTransform.speed) <= cCol.y)
                player.getComponent<TransformComponent>().position.y = cCol.y - playerTransform.height * playerTransform.scale - 1;
            else if (direction.E && playerTransform.position.x + (playerTransform.width * playerTransform.scale) - (playerTransform.velocity.x * playerTransform.speed) <= cCol.x)
                player.getComponent<TransformComponent>().position.x = cCol.x - (playerTransform.width * playerTransform.scale) - 1;
            else if (direction.W && playerTransform.position.x - playerTransform.velocity.x * playerTransform.speed >= cCol.x + cCol.w)
                player.getComponent<TransformComponent>().position.x = cCol.x + cCol.w + 1;
        }
    }
    
    for (auto& p : projectiles) {
        SDL_Rect projectileCol = p->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(projectileCol, playerCol)) {
            p->destroy();
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
    for (auto& p : projectiles)
        p->draw();
    
    playerPosLabel.draw();
    colliderPosLabel.draw();
    
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
