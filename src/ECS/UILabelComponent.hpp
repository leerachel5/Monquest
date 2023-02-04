#ifndef UILabelComponent_hpp
#define UILabelComponent_hpp

#include "ECS.hpp"
#include "../AssetManager.hpp"
#include "../Game.hpp"
#include "TransformComponent.hpp"
#include "ProjectorComponent.hpp"
#include <SDL2_ttf/SDL_ttf.h>
#include <string>

class UILabelComponent : public Component {
public:
    UILabelComponent() = default;
    UILabelComponent(int xoffset, int yoffset, std::string labelText, std::string textFontID, int textFontSize, SDL_Color& tColor) {
        SetLabelPosition(xoffset, yoffset);
        SetLabelText(labelText);
        SetLabelFont(textFontID, textFontSize, tColor);
    }
    
    ~UILabelComponent() {
    }
    
    void SetLabelText(std::string labelText) {
        text = labelText;
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
    }
    
    void update() override {
        textTexture = FontManager::SetText(font, fontSize, text, textColor);
        
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
    
    std::string text;
    SDL_Texture* textTexture;
    
    ProjectorComponent* projector;
};

#endif /* UILabelComponent_hpp */
