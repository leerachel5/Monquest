#include "Game.hpp"


int main() {
    const int FPS = 60;
    const int TIME_BETWEEN_FRAMES = 600;
    const int FRAME_DELAY = TIME_BETWEEN_FRAMES / FPS;
    
    Uint32 frameStart;
    int frameTime;
    
    Game *game = new Game();
    game->init("Monquest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640);
    
    while (game->running()) {
        frameStart = SDL_GetTicks();
        
        game->handleEvents();
        game->update();
        game->render();
        
        frameTime = SDL_GetTicks() - frameStart;
        
        if (FRAME_DELAY > frameTime)
            SDL_Delay(FRAME_DELAY - frameTime);
    }
    
    game->clean();
}
