#ifndef OverworldState_hpp
#define OverworldState_hpp

#include "GameState.hpp"

class OverworldState : public GameState {
public:
    OverworldState();
    ~OverworldState();
    
    // State transitions
    void enter() override;
    void exit() override;
    
    // Main loop functions
    void init() override;
    void handleEvents(SDL_Event& event) override;
    void update() override;
    void render() override;

private:
    Entity* player;
    Entity* playerPosLabel;
    
    std::vector<Entity*>& tiles;
    std::vector<Entity*>& mapLinks;
    std::vector<Entity*>& players;
    std::vector<Entity*>& colliders;
    
    bool isRunning;
};

#endif /* OverworldState_hpp */
