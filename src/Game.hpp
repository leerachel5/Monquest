#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <vector>

class ColliderComponent;

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
    
    static void AddTile(int srcX, int srcY, int xpos, int ypos);
    
public:
    static SDL_Renderer* renderer;
    static SDL_Event event;
    static SDL_Rect camera;
    static std::vector<ColliderComponent*> colliders;
    
    static bool isRunning;
    
private:
    int cnt;
    SDL_Window *window;
};

#endif /* Game_hpp */
