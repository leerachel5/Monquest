#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>

class Game {
public:
    Game();
    ~Game();
    
    void init(const char* title, int xpos, int ypos, int width, int height);
    
    void handleEvents();
    void update();
    void render();
    void clean();
    
    inline bool running() {return isRunning; }
    
    static SDL_Renderer* renderer;
    
private:
    int cnt;
    bool isRunning;
    SDL_Window *window;
};

#endif /* Game_hpp */
