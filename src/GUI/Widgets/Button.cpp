#include "Button.hpp"
#include "../../AssetManager.hpp"
#include "../../Collision.hpp"

Button::Button() {}

Button::Button(int xpos, int ypos, int w, int h, int sc) : TextBox(xpos, ypos, w, h, sc) {}

Button::Button(int xpos, int ypos, int w, int h, int sc, std::string texID, std::string buttonText, std::string fontID, int fontSz, SDL_Color tColor, void (*f) ())
: TextBox(xpos, ypos, w, h, sc, texID, buttonText, fontID, fontSz, tColor), func{f} {}

Button::Button(int xpos, int ypos, int w, int h, int sc, std::string texID, std::string buttonText, std::string fontID, int fontSz, SDL_Color tColor, void (*f) (), bool enableHoverAnim)
: TextBox(xpos, ypos, w, h, sc, texID, buttonText, fontID, fontSz, tColor), func{f}, enableHoverAnimation(enableHoverAnim) {
    if (enableHoverAnim)
        hoverSrcRect = { srcRect->x + srcRect->w , srcRect->y, srcRect->w, srcRect->h };
}

Button::~Button() {}

void Button::handleEvents(SDL_Event &event) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect mouse = {mouseX, mouseY, 1, 1};
    
    if (Collision::AABB(mouse, *destRect)) {
        switch(event.type){
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        func();
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        isHovering = true;
    } else {
        isHovering = false;
    }
}

void Button::draw() {
    if (enableHoverAnimation && isHovering) {
        TextureManager::Draw(backgroundTex, &hoverSrcRect, destRect);
    }
    else
        TextureManager::Draw(backgroundTex, srcRect, destRect);
    
    FontManager::Draw(textTexture, destRect->x + destRect->w / 10, destRect->y + destRect->h / 5, *srcRect, *destRect);
}

void Button::setFunction(void (*f) ()) {
    func = f;
}

void Button::toggleHoverAnimation(bool flag) {
    if (flag)
        hoverSrcRect = { srcRect->x + srcRect->w , srcRect->y, srcRect->w, srcRect->h };
    enableHoverAnimation = flag;
}
