#ifndef MainMenuState_hpp
#define MainMenuState_hpp

#include "GameState.hpp"

class MainMenuState : public GameState {
public:
    MainMenuState();
    ~MainMenuState();
    
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
        groupButtons
    };
    
private:
    std::vector<Entity*>& buttons;
};

#endif /* MainMenuState_hpp */
