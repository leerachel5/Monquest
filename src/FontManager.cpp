#include "FontManager.hpp"
#include "Game.hpp"
#include <iostream>


TTF_Font *FontManager::LoadFont(const char *path, int fontSize) {
    TTF_Font* f = TTF_OpenFont(path, fontSize);
    if (f == NULL) {
        std::cout << "Could not load font at path \"" << path << "\"" << std::endl;
        exit(1);
    }
    return f;
}

SDL_Texture *FontManager::SetText(TTF_Font* font, int fontSize, std::string text, SDL_Color textColor) {
    TTF_SetFontSize(font, fontSize);
    
    SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
    SDL_FreeSurface(surf);
    
    return texture;
}

void FontManager::Draw(SDL_Texture* texture, int x, int y) {
    SDL_Rect position = { x, y, 0, 0 };
    SDL_QueryTexture(texture, nullptr, nullptr, &position.w, &position.h);
    
    SDL_RenderCopy(Game::renderer, texture, nullptr, &position);
}
