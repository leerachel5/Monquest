#ifndef Button_hpp
#define Button_hpp

#include <string>
#include <SDL2_ttf/SDL_ttf.h>
#include "Widget.hpp"

class AssetManager;

class Button : public Widget {
public:
    Button();
    Button(int xpos, int ypos, int w, int h, int sc, void (*f) (), std::string buttonText, std::string texID, std::string fontID, SDL_Color tColor);
    ~Button() override;
    
    // Main loop functions
    void init() override;
    void handleEvents(SDL_Event& event) override;
    void update() override;
    void draw() override;
    
private:
    SDL_Texture* backgroundTex;
    SDL_Texture* textTexture;
    std::string text;
    TTF_Font* font;
    SDL_Color textColor;
    void (*func) ();
    
    SDL_Rect hoverSrcRect;
    bool isHovering = false;
};

#endif /* Button_hpp */
