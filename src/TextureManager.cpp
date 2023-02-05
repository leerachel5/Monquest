#include "TextureManager.hpp"
#include "Game.hpp"
#include <iostream>
#include <SDL2_image/SDL_image.h>


SDL_Texture* TextureManager::LoadTexture(const char *texture) {
    SDL_Surface *tempSurface = IMG_Load(texture);
    if (tempSurface == NULL) {
        std::cout << "Could not load surface at path \"" << texture << "\"" << std::endl;
        exit(1);
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    if (tex == NULL) {
        std::cout << "Could not create texture at path \"" << texture << "\"" << std::endl;
        exit(1);
    }
    SDL_FreeSurface(tempSurface);
    
    return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dest) {
    SDL_RenderCopy(Game::renderer, tex, src, dest);
}
