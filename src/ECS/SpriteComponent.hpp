#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "Components.hpp"
#include "TextureManager.hpp"
#include "Animation.hpp"
#include <map>
#include <SDL2/SDL.h>

class SpriteComponent : public Component {
public:
    SpriteComponent() = default;
    SpriteComponent(std::string id) {
        setTex(id);
    }
    
    SpriteComponent(std::string id, bool isAnimated) {
        animated = isAnimated;
        
        Animation idleSouth = Animation(0, 1, 100);
        Animation walkSouth = Animation(1, 4, 100);
        Animation idleWest = Animation(2, 1, 100);
        Animation walkWest = Animation(3, 4, 100);
        Animation idleEast = Animation(4, 1, 100);
        Animation walkEast = Animation(5, 4, 100);
        Animation idleNorth = Animation(6, 1, 100);
        Animation walkNorth = Animation(7, 4, 100);
        
        animations.emplace("IdleSouth", idleSouth);
        animations.emplace("WalkSouth", walkSouth);
        animations.emplace("IdleWest", idleWest);
        animations.emplace("WalkWest", walkWest);
        animations.emplace("IdleEast", idleEast);
        animations.emplace("WalkEast", walkEast);
        animations.emplace("IdleNorth", idleNorth);
        animations.emplace("WalkNorth", walkNorth);
        
        Play("IdleSouth");
        
        setTex(id);
    }
    
    ~SpriteComponent() {
    }

    void setTex(std::string id) {
        texture = Game::assets->GetTexture(id);
    }

    void init() {
        facingDirection = "South";
        transform = &entity->getComponent<TransformComponent>();
        
        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }

    void update() {
        if (animated) {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
            srcRect.y = animIndex * transform->height;
        }
        
        destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
        destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void draw() {
        TextureManager::Draw(texture, &srcRect, &destRect);
    }
    
    void Play(std::string animName) {
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }

public:
    int animIndex = 0;
    std::map<std::string, Animation> animations;
    std::string facingDirection;

private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    
    bool animated = false;
    int frames = 0;
    int speed = 100;
};

#endif /* SpriteComponent_hpp */
