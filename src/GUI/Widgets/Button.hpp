#ifndef Button_hpp
#define Button_hpp

#include <string>
#include "TextBox.hpp"

class AssetManager;

class Button : public TextBox {
public:
    Button();
    Button(int xpos, int ypos, int w, int h, int sc);
    Button(int xpos, int ypos, int w, int h, int sc, std::string buttonText, std::string texID, std::string fontID, int fontSz, SDL_Color tColor, void (*f) ());
    Button(int xpos, int ypos, int w, int h, int sc, std::string texID, std::string buttonText, std::string fontID, int fontSz, SDL_Color tColor, void (*f) (), bool enableHoverAnim);
    ~Button() override;
    
    // Main loop functions
    void handleEvents(SDL_Event& event) override;
    void draw() override;
    
    // Mutator member functions
    void setFunction(void (*f) ());
    void toggleHoverAnimation(bool flag);
    
private:
    void (*func) ();
    
    bool enableHoverAnimation = false;
    SDL_Rect hoverSrcRect;
    bool isHovering = false;
};

#endif /* Button_hpp */
