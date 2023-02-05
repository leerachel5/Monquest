#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <vector>

class AssetManager;
class ColliderComponent;
class CreatureManager;

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
    
public:
    static SDL_Renderer* renderer;
    static SDL_Event event;
    static SDL_Rect camera;
    static AssetManager* assets;
    static CreatureManager* creatures;
    static bool isRunning;
    static int windowW, windowH;
    
private:
    int cnt;
    SDL_Window *window;
};

#endif /* Game_hpp */
