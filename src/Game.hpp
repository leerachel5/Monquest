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
    
    static void AddTile(int id, int x, int y);
    
    static SDL_Renderer* renderer;
    static SDL_Event event;
    static std::vector<ColliderComponent*> colliders;
    
private:
    int cnt;
    bool isRunning;
    SDL_Window *window;
};

#endif /* Game_hpp */
