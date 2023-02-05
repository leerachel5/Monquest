#include "TileComponent.hpp"
#include "Game.hpp"
#include "AssetManager.hpp"
#include "TextureManager.hpp"

namespace {
    typedef std::shared_ptr<SDL_Texture> SharedTexture;

    inline SharedTexture make_shared(SDL_Texture* texture) {
        return SharedTexture(texture, SDL_DestroyTexture);
    }
}


TileComponent::TileComponent() {}

TileComponent::~TileComponent() {
    if (texture.unique())
        SDL_DestroyTexture(texture.get());
}

TileComponent::TileComponent(std::string id, int srcX, int srcY, int xpos, int ypos, int tsize, int tscale) : texture{make_shared(Game::assets->GetTexture(id))} {
    position.x = xpos;
    position.y = ypos;
    
    srcRect.x = srcX;
    srcRect.y = srcY;
    srcRect.w = srcRect.h = tsize;
    
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = destRect.h = tsize * tscale;
}

void TileComponent::update() {
    destRect.x = position.x - Game::camera.x;
    destRect.y = position.y - Game::camera.y;
}

void TileComponent::draw() {
    TextureManager::Draw(texture.get(), &srcRect, &destRect);
}
