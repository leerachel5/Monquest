#include "AssetManager.hpp"

AssetManager::AssetManager() {}

AssetManager::~AssetManager(){
}

void AssetManager::AddTexture(std::string id, const char *path) {
    textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id) {
    return textures[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize) {
    TTF_Font* f = TTF_OpenFont(path.c_str(), fontSize);
    if (f == NULL) {
        std::cout << "Could not load font at path \"" << path << "\"" << std::endl;
        exit(1);
    }
    fonts.emplace(id, f);
}

TTF_Font* AssetManager::GetFont(std::string id) {
    return fonts[id];
}
