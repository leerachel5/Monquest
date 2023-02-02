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

public:
    enum groupLabels : std::size_t {
        groupMap,
        groupMapLinks,
        groupPlayers,
        groupColliders,
        groupTallGrass
    };

private:
    Entity* player;
    
    std::vector<Entity*>& tiles;
    std::vector<Entity*>& mapLinks;
    std::vector<Entity*>& players;
    std::vector<Entity*>& colliders;
    std::vector<Entity*>& tallGrass;
};

#endif /* OverworldState_hpp */
