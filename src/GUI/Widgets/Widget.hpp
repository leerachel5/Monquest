#ifndef Widget_hpp
#define Widget_hpp

#include <SDL2/SDL.h>
#include "Game.hpp"

class Widget {
public:
    Widget() {}
    Widget(int xpos, int ypos, int w, int h, int sc) {
        srcRect = new SDL_Rect{ 0, 0, w, h };
        destRect = new SDL_Rect{ xpos, ypos, w * sc, h * sc };
    }
    
    virtual ~Widget() {}
    
    // Main loop functions
    virtual void init() = 0;
    virtual void handleEvents(SDL_Event& event) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    
    void setXToPercentOfWindow(int percent) {
        destRect->x = Game::windowW * percent / 100;
    }
    
    void setYToPercentOfWindow(int percent) {
        destRect->y = Game::windowW * percent / 100;
    }
    
    void setWidthToPercentOfWindow(int percent) {
        destRect->w = Game::windowW * percent / 100;
    }
    
    void setHeightToPercentOfWindow(int percent) {
        destRect->h = Game::windowH * percent / 100;
    }
    
public:
    SDL_Rect* srcRect;
    SDL_Rect* destRect;
};

#endif /* Widget_hpp */
