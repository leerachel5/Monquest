#ifndef TextBox_hpp
#define TextBox_hpp

#include "Widget.hpp"
#include <SDL2_ttf/SDL_ttf.h>
#include <string>


class TextBox : public Widget {
public:
    TextBox();
    TextBox(int xpos, int ypos, int w, int h, int sc);
    TextBox(int xpos, int ypos, int w, int h, int sc, std::string buttonText, std::string texID, std::string fontID, int fontSize, SDL_Color tColor);
    ~TextBox() override;
    
    // Main loop functions
    void init() override;
    void handleEvents(SDL_Event& event) override;
    void update() override;
    void draw() override;
    
    // Mutator member functions
    void setTexture(std::string texID);
    void setFont(std::string fontID, int fontSize, SDL_Color tColor);
    void setText(std::string buttonText);
    
protected:
    SDL_Texture* backgroundTex;
    
    SDL_Texture* textTexture;
    std::string text;
    TTF_Font* font;
    int fontSize;
    SDL_Color textColor;
};


#endif /* TextBox_hpp */
