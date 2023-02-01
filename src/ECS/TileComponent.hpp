#ifndef TileComponent_hpp
#define TileComponent_hpp

#include "ECS.hpp"
#include <SDL2/SDL.h>

namespace {
    typedef std::shared_ptr<SDL_Texture> SharedTexture;

    inline SharedTexture make_shared(SDL_Texture* texture) {
        return SharedTexture(texture, SDL_DestroyTexture);
    }
}


class TileComponent : public Component {
public:
    TileComponent() = default;
    ~TileComponent() {
        if (texture.unique())
            SDL_DestroyTexture(texture.get());
    }
    
    TileComponent(std::string id, int srcX, int srcY, int xpos, int ypos, int tsize, int tscale) : texture{make_shared(Game::assets->GetTexture(id))} {
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
        TextureManager::Draw(texture.get(), srcRect, destRect);
    }
    
public:
    SharedTexture texture;
    SDL_Rect srcRect, destRect;
    Vector2D position;
};

#endif /* TileComponent_hpp */
