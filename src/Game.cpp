#include "Game.hpp"
#include "GameStates/GameStates.hpp"

Manager manager;
GameState* overworldState;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = {0,0,800,640};

AssetManager* Game::assets = new AssetManager();

bool Game::isRunning = false;

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
    
    overworldState = new OverworldState();
    overworldState->init();
}

void Game::handleEvents() {
    SDL_PollEvent(&event);
    overworldState->handleEvent(event);
}

void Game::update() {
    overworldState->update();
}

void Game::render() {
    SDL_RenderClear(renderer);
    
    overworldState->render();
    
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
