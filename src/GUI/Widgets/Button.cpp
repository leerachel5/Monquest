#include "Button.hpp"
#include "../../AssetManager.hpp"
#include "../../Collision.hpp"

Button::Button() {}

Button::Button(int xpos, int ypos, int w, int h, int sc, void (*f) (), std::string buttonText, std::string texID, std::string fontID, SDL_Color tColor)
: Widget(xpos, ypos, w, h, sc), func{f}, text{buttonText}, textColor{tColor} {
    backgroundTex = Game::assets->GetTexture(texID);
    font = Game::assets->GetFont(fontID);
    
    hoverSrcRect = { srcRect.x + srcRect.w , srcRect.y, srcRect.w, srcRect.h };
}

Button::~Button() {}

void Button::init() {}

void Button::handleEvents(SDL_Event &event) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect mouse = {mouseX, mouseY, 1, 1};
    
    if (Collision::AABB(mouse, destRect)) {
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

void Button::update() {
    textTexture = FontManager::SetText(font, destRect.h / 2, text, textColor);
}

void Button::draw() {
    if (isHovering)
        TextureManager::Draw(backgroundTex, hoverSrcRect, destRect);
    else
        TextureManager::Draw(backgroundTex, srcRect, destRect);
    
    FontManager::Draw(textTexture, destRect.x + destRect.w / 10, destRect.y + destRect.h / 5, srcRect, destRect);
}
