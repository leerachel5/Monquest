#ifndef UILabelComponent_hpp
#define UILabelComponent_hpp

#include "ECS.hpp"
#include "../Vector2D.hpp"
#include <SDL2_ttf/SDL_ttf.h>
#include <string>

class TextComponent;
class ProjectorComponent;


class UILabelComponent : public Component {
public:
    UILabelComponent();
    UILabelComponent(int xoffset, int yoffset, std::string textFontID, int textFontSize, SDL_Color& tColor);
    ~UILabelComponent();
    
    // Main loop functions
    void init() override;
    void update() override;
    void draw() override;
    
    // Mutator methods
    void SetLabelFont(std::string fontID, int fontSz, SDL_Color tColor);
    void SetLabelPosition(int xoffset, int yoffset);
    
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
