#ifndef AssetManager_hpp
#define AssetManager_hpp

#include <SDL2_ttf/SDL_ttf.h>
#include <map>
#include <string>
#include "ECS/ECS.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"

class AssetManager {
public:
    AssetManager();
    ~AssetManager();
    
    // Texture Management
    void AddTexture(std::string id, const char* path);
    SDL_Texture* GetTexture(std::string id);
    
    void AddFont(std::string id, std::string path, int fontSize);
    TTF_Font* GetFont(std::string id);
    
private:
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;
};

#endif /* AssetManager_hpp */
