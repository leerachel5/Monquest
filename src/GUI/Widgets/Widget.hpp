#ifndef Widget_hpp
#define Widget_hpp

#include <SDL2/SDL.h>

class Widget {
public:
    Widget() {}
    Widget(int xpos, int ypos, int w, int h, int sc) {
        srcRect = { 0, 0, w, h };
        destRect = { xpos, ypos, w * sc, h * sc };
    }
    
    virtual ~Widget() {}
    
    // Main loop functions
    virtual void init() = 0;
    virtual void handleEvents(SDL_Event& event) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    
public:
    SDL_Rect srcRect, destRect;
};

#endif /* Widget_hpp */
