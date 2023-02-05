#ifndef GameState_hpp
#define GameState_hpp

#include "../ECS/ECS.hpp"
#include <SDL2/SDL.h>

class Manager;
class MapManager;


class GameState {
public:
    GameState();
    virtual ~GameState() {}
    
    // State transitions
    virtual void enter() = 0;
    virtual void exit() = 0;
    
    // Main loop functions
    virtual void init() = 0;
    virtual void handleEvents(SDL_Event& e) = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    
protected:
    Manager manager;
    MapManager* mapManager;
    
    SDL_Rect camera;
};

#endif /* GameState_hpp */
