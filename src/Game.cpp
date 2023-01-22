#include "Game.hpp"
#include "TextureManager.hpp"

namespace {
    SDL_Texture *playerTex;
    SDL_Rect srcR, destR;
}

const int PLAYER_HEIGHT = 100;
const int PLAYER_WIDTH = 100;


Game::Game()
{}

Game::~Game()
{}

void Game::init(const char *title, int xpos, int ypos, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems Initialized!..." << std::endl;
        
        window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
        if (window)
            std::cout << "Window created!..." << std::endl;
        
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!..." << std::endl;
        }
        
        isRunning = true;
    } else {
        isRunning = false;
    }
    
    playerTex = TextureManager::LoadTexture("assets/player.png", renderer);
}

void Game::handleEvents() {
    SDL_Event event;
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
    cnt++;
    destR.h = PLAYER_HEIGHT;
    destR.w = PLAYER_WIDTH;
    destR.x = cnt;
}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, playerTex, NULL, &destR);
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned!" << std::endl;
}
