#ifndef BattleState_hpp
#define BattleState_hpp

#include "GameState.hpp"


class BattleState : public GameState {
public:
    BattleState();
    ~BattleState();
    
    // State transitions
    void enter() override;
    void exit() override;
    
    // Main loop functions
    void init() override;
    void handleEvents(SDL_Event& event) override;
    void update() override;
    void render() override;

private:
    SDL_Texture* battlegroundTexture;
    
    enum groupLabels : std::size_t {
        groupWidgets
    };
    std::vector<Entity*>& widgets;
};

#endif /* BattleState_hpp */
