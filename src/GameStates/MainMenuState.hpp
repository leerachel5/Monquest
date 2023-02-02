#ifndef MainMenuState_hpp
#define MainMenuState_hpp

#include "GameState.hpp"
#include "../Widgets/Widgets.hpp"


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
    
private:
    std::vector<Widget*> widgets;
};

#endif /* MainMenuState_hpp */
