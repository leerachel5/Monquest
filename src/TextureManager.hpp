#ifndef TextureManager_hpp
#define TextureManager_hpp

class SDL_Texture;
class SDL_Rect;

class TextureManager {
public:
    static SDL_Texture *LoadTexture(const char *fileName);
    static void Draw(SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dest);
};

#endif /* TextureManager_hpp */
