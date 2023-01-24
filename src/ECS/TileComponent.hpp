#ifndef TileComponent_hpp
#define TileComponent_hpp

#include "ECS.hpp"
#include <SDL2/SDL.h>

class TileComponent : public Component {
public:
    TileComponent() = default;
    ~TileComponent() {
        SDL_DestroyTexture(texture);
    }
    
    TileComponent(const char* path, int srcX, int srcY, int xpos, int ypos) {
        texture = TextureManager::LoadTexture(path);
        
        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = 32;
        
        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = destRect.h = 64;
    }
    
    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect);
    }
    
public:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
};

#endif /* TileComponent_hpp */
