#ifndef UILabelComponent_hpp
#define UILabelComponent_hpp

#include "ECS.hpp"
#include "../AssetManager.hpp"
#include "../Game.hpp"
#include "TextComponent.hpp"
#include "ProjectorComponent.hpp"
#include <SDL2_ttf/SDL_ttf.h>
#include <string>

class UILabelComponent : public Component {
public:
    UILabelComponent() = default;
    UILabelComponent(int xoffset, int yoffset, std::string textFontID, int textFontSize, SDL_Color& tColor) {
        SetLabelPosition(xoffset, yoffset);
        SetLabelFont(textFontID, textFontSize, tColor);
    }
    
    ~UILabelComponent() {
    }
    
    void SetLabelFont(std::string fontID, int fontSz, SDL_Color tColor) {
        font = Game::assets->GetFont(fontID);
        fontSize = fontSz;
        textColor = tColor;
    }
    
    void SetLabelPosition(int xoffset, int yoffset) {
        xOffset = xoffset;
        yOffset = yoffset;
    }
    
    void init() override {
        projector = &entity->getComponent<ProjectorComponent>();
        text = &entity->getComponent<TextComponent>();
    }
    
    void update() override {
        textTexture = FontManager::SetText(font, fontSize, text->getText(), textColor);
        
        position.x = projector->destRect.x + xOffset;
        position.y = projector->destRect.y + yOffset;
    }
    
    void draw() override {
        FontManager::Draw(textTexture, position.x, position.y);
    }
    
private:
    int xOffset, yOffset;
    Vector2D position; // Position is relative to its enclosing bounding box
    
    TTF_Font* font;
    int fontSize;
    SDL_Color textColor;
    
    TextComponent* text;
    SDL_Texture* textTexture;
    
    ProjectorComponent* projector;
};

#endif /* UILabelComponent_hpp */
