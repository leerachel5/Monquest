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
    
    TileComponent(const char* path, int srcX, int srcY, int xpos, int ypos, int tsize, int tscale) {
        texture = TextureManager::LoadTexture(path);
        
        position.x = xpos;
        position.y = ypos;
        
        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = srcRect.h = tsize;
        
        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = destRect.h = tsize * tscale;
    }
    
    void update() override {
        destRect.x = position.x - Game::camera.x;
        destRect.y = position.y - Game::camera.y;
    }
    
    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect);
    }
    
public:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    Vector2D position;
};

#endif /* TileComponent_hpp */
