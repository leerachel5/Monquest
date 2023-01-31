#ifndef GameState_hpp
#define GameState_hpp

#include "../MapManager.hpp"
#include "../AssetManager.hpp"
#include "../ECS/Components.hpp"

class GameState {
public:
    GameState() : mapManager{new MapManager()} {}
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
};

#endif /* GameState_hpp */
