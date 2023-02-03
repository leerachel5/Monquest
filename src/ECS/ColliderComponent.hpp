#ifndef ColliderComponent_hpp
#define ColliderComponent_hpp

#include <string>
#include <SDL2/SDL.h>
#include "Components.hpp"
#include "../TextureManager.hpp"

class ColliderComponent : public Component {
public:
    
    ColliderComponent(std::string t)
        : tag{t}
    {}
    
    ColliderComponent(std::string t, int xpos, int ypos, int size) {
        tag = t;
        collider.x = xpos;
        collider.y = ypos;
        collider.w = collider.h = size;
    }
    
    void init() override {
        if (!entity->hasComponent<TransformComponent>())
            entity->addComponent<TransformComponent>();
        
        transform = &entity->getComponent<TransformComponent>();
        
        tex = TextureManager::LoadTexture("assets/colTex.png");
        srcRect = {0, 0, 32, 32};
        destRect = {collider.x, collider.y, collider.w, collider.h};
        
    }
    
    void update() override {
        if (tag != "terrain") {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
        }
        
        destRect.x = collider.x - Game::camera.x;
        destRect.y = collider.y - Game::camera.y;
    }
    
    void draw() override {
        TextureManager::Draw(tex, &srcRect, &destRect);
    }

public:
    SDL_Rect collider;
    std::string tag;
    
    SDL_Texture* tex;
    SDL_Rect srcRect, destRect;
    
    TransformComponent* transform;
};

#endif /* ColliderComponent_hpp */
