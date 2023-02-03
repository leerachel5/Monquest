#ifndef MainMenuState_hpp
#define MainMenuState_hpp

#include "GameState.hpp"
#include "../GUI/Widgets/Widgets.hpp"
#include "../GUI/Layouts/Layouts.hpp"


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
    std::map<std::string, Layout<Widget*>*> layouts;
};

#endif /* MainMenuState_hpp */
