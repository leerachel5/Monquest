#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "Components.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL.h>

class SpriteComponent : public Component {
public:
    SpriteComponent(const char* texturePath) {
        setTex(texturePath);
    }
    
    ~SpriteComponent() {
        SDL_DestroyTexture(texture);
    }

    void setTex(const char* texturePath) {
        texture = TextureManager::LoadTexture(texturePath);
    }

    void init() {
        transform = &entity->getComponent<TransformComponent>();
        
        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }

    void update() {
        destRect.x = (int)transform->position.x;
        destRect.y = (int)transform->position.y;
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void draw() {
        TextureManager::Draw(texture, srcRect, destRect);
    }


private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
};

#endif /* SpriteComponent_hpp */
