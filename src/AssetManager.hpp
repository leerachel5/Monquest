#ifndef AssetManager_hpp
#define AssetManager_hpp

#include <map>
#include <string>

class SDL_Texture;
class _TTF_Font;


class AssetManager {
public:
    AssetManager();
    ~AssetManager();
    
    // Texture Management
    void AddTexture(std::string id, const char* path);
    SDL_Texture* GetTexture(std::string id);
    
    void AddFont(std::string id, std::string path, int fontSize);
    _TTF_Font* GetFont(std::string id);
    
private:
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, _TTF_Font*> fonts;
};

#endif /* AssetManager_hpp */
