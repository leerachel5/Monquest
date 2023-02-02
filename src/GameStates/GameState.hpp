#ifndef GameState_hpp
#define GameState_hpp

#include "../MapManager.hpp"
#include "../ECS/Components.hpp"

class GameState {
public:
    GameState() : mapManager{new MapManager()}, isRunning{false} {}
    virtual ~GameState() {}
    
    // State transitions
    virtual void enter() = 0;
    virtual void exit() = 0;
    
    // Main loop functions
    virtual void init() = 0;
    virtual void handleEvents(SDL_Event& e) = 0;
    virtual void update() = 0;
    virtual void render() = 0;

public:
    bool isRunning;
    
protected:
    Manager manager;
    MapManager* mapManager;
    
    SDL_Rect camera = {0, 0, Game::windowW, Game::windowH};
};

#endif /* GameState_hpp */
