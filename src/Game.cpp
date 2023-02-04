#include "Game.hpp"
#include "StateManager.hpp"

Manager manager;
StateManager states;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera;
int Game::windowW;
int Game::windowH;

AssetManager* Game::assets = new AssetManager();

bool Game::isRunning = false;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char *title, int xpos, int ypos, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
        windowW = width;
        windowH = height;
        
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        
        isRunning = true;
    } else {
        isRunning = false;
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cout << "Error: SDL_image failed to initialize" << std::endl;
        exit(1);
    }
    if (TTF_Init() == -1) {
        std::cout << "Error: SDL_TTF failed to initialize" << std::endl;
        exit(1);
    }

    assets->AddTexture("terrain", "assets/terrain_ss.png");
    assets->AddTexture("tall grass", "assets/tall_grass.png");
    assets->AddTexture("player", "assets/player.png");
    assets->AddTexture("button", "assets/button.png");
    assets->AddTexture("dialogue box", "assets/dialogue_box.png");
    assets->AddTexture("battleground", "assets/battleground.png");
    
    assets->AddFont("Arial", "assets/Arial.ttf", 16);
    
    states.addState("overworld", new OverworldState());
    states.addState("main menu", new MainMenuState());
    states.addState("battle", new BattleState());
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
                        states.exitState();
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
