#include "Game.hpp"
#include "StateManager.hpp"

Manager manager;
StateManager states;

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
    assets->AddTexture("start_button", "assets/start_button.png");
    
    assets->AddFont("Arial", "assets/Arial.ttf", 16);
    
    states.addState("overworld", new OverworldState());
    states.addState("main menu", new MainMenuState());
    states.enterState("main menu");
    states.init();
}

void Game::handleEvents() {
    SDL_PollEvent(&event);
    
    if (isRunning) {
        switch(event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        if (states.isRunning("overworld")) {
                            states.enterState("main menu");
                            states.exitState("overworld");
                        } else if (states.isRunning("main menu")) {
                            states.enterState("overworld");
                            states.exitState("main menu");
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
            
            case SDL_QUIT:
                Game::isRunning = false;
                break;
                
            default:
                break;
        }
    }
    
    states.handleEvents(event);
}

void Game::update() {
    states.update();
}

void Game::render() {
    SDL_RenderClear(renderer);
    
    states.render();
    
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
