#ifndef StateManager_hpp
#define StateManager_hpp

#include "GameStates/GameStates.hpp"
#include <unordered_map>


class StateManager {
public:
    StateManager();
    ~StateManager();
    
    void addState(std::string stateID, GameState* state);
    void enterState(std::string stateID);
    void exitState();
    
    bool isRunning(std::string stateID);
    
    void init();
    void handleEvents(SDL_Event& event);
    void update();
    void render();

public:
    const static std::string START_STATE;
    const static std::string DEFAULT_STATE;
    
    std::string activeState;
    std::string prevState;
    
private:
    std::unordered_map<std::string, GameState*> states;
};

#endif /* StateManager_hpp */
