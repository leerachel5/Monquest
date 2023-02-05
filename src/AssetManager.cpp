#include "AssetManager.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include <SDL2_ttf/SDL_ttf.h>


AssetManager::AssetManager() {}

AssetManager::~AssetManager(){
    for (std::pair<std::string, SDL_Texture*> p : textures) {
        SDL_DestroyTexture(p.second);
    }
}

void AssetManager::AddTexture(std::string id, const char *path) {
    textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id) {
    return textures.at(id);
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize) {
    fonts.emplace(id, FontManager::LoadFont(path.c_str(), fontSize));
}

_TTF_Font* AssetManager::GetFont(std::string id) {
    return fonts.at(id);;
}
