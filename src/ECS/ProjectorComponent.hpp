#ifndef ProjectorComponent_hpp
#define ProjectorComponent_hpp

#include "ECS.hpp"
#include "Animation.hpp"
#include "TransformComponent.hpp"
#include <unordered_map>

class ProjectorComponent : public Component {
public:
    ProjectorComponent() {}
    ProjectorComponent(bool isAnimated) : animated{isAnimated} {}
    ~ProjectorComponent() {}
    
    // Main loop functions
    void init() override {
        transform = &entity->getComponent<TransformComponent>();
        
        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }
    
    void update() override {
        if (animated) {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
            srcRect.y = animIndex * transform->height;
        }
        
        if (!fixedX)
            destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
        if (!fixedY)
            destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
        if (!fixedW)
            destRect.w = transform->width * transform->scale;
        if (!fixedH)
            destRect.h = transform->height * transform->scale;
    }
    
    // Animations
    void AddAnimation(std::string animName, int index, int frames, int speed) {
        Animation anim = Animation(index, frames, speed);
        animations.emplace(animName, anim);
    }
    
    void PlayAnimation(std::string animName) {
        animIndex = animations[animName].index;
        frames = animations[animName].frames;
        speed = animations[animName].speed;
    }
    
    void ToggleAnimation(bool flag) {
        animated = flag;
    }
    
    // Mutator member functions
    void setXToPercentOfWindow(int percent) {
        destRect.x = Game::windowW * percent / 100;
        fixedX = true;
    }
    void setYToPercentOfWindow(int percent) {
        destRect.y = Game::windowH * percent / 100;
        fixedY = true;
    }
    void setWidthToPercentOfWindow(int percent) {
        destRect.w = Game::windowW * percent / 100;
        fixedW = true;
    }
    void setHeightToPercentOfWindow(int percent) {
        destRect.h = Game::windowH * percent / 100;
        fixedH = true;
    }
    
    
public:
    SDL_Rect srcRect, destRect;

private:
    TransformComponent* transform;
    
    bool animated = false;
    int animIndex = 0;
    int frames = 0;
    int speed = 0;
    std::unordered_map<std::string, Animation> animations;
    
    // When true, projection is independent of the entity's TransformComponent
    bool fixedX = false;
    bool fixedY = false;
    bool fixedW = false;
    bool fixedH = false;
};

#endif /* ProjectorComponent_hpp */
