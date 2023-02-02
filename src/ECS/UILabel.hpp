#ifndef UILabel_hpp
#define UILabel_hpp

#include "ECS.hpp"
#include "../AssetManager.hpp"
#include "../Game.hpp"

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>

class UILabel : public Component {
public:
    UILabel(int xpos, int ypos, std::string labelText, std::string textFont, int textFontSize, SDL_Color& color)
        : text{labelText}, font{textFont}, fontSize{textFontSize}, textColor{color}
    {
        position.x = xpos;
        position.y = ypos;
        
        SetLabelText(text, font, fontSize);
    }
    ~UILabel() {
    }
    
    void SetLabelText(std::string text, std::string textFont, int fontSize) {
        TTF_Font* font = Game::assets->GetFont(textFont);
        TTF_SetFontSize(font, fontSize);
        
        SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), textColor);
        texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
        SDL_FreeSurface(surf);
        
        SDL_QueryTexture(texture, nullptr, nullptr, &position.w, &position.h);
    }
    
    
    void draw() override {
        
        SDL_RenderCopy(Game::renderer, texture, nullptr, &position);
    }
    
private:
    SDL_Rect position;
    std::string text;
    std::string font;
    int fontSize;
    SDL_Color textColor;
    SDL_Texture* texture;
};

#endif /* UILabel_hpp */
