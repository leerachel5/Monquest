#include "ProjectorComponent.hpp"
#include "../Game.hpp"
#include "TransformComponent.hpp"

ProjectorComponent::ProjectorComponent() {}
ProjectorComponent::ProjectorComponent(bool isAnimated) : animated{isAnimated} {}
ProjectorComponent::~ProjectorComponent() {}

// Main loop functions
void ProjectorComponent::init() {
    transform = &entity->getComponent<TransformComponent>();
    
    srcRect.x = srcRect.y = 0;
    srcRect.w = transform->width;
    srcRect.h = transform->height;
}

void ProjectorComponent::update() {
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
void ProjectorComponent::AddAnimation(std::string animName, int index, int frames, int speed) {
    Animation anim = Animation(index, frames, speed);
    animations.emplace(animName, anim);
}

void ProjectorComponent::PlayAnimation(std::string animName) {
    animIndex = animations[animName].index;
    frames = animations[animName].frames;
    speed = animations[animName].speed;
}

void ProjectorComponent::ToggleAnimation(bool flag) {
    animated = flag;
}

// Mutator member functions
void ProjectorComponent::setXToPercentOfWindow(int percent) {
    destRect.x = Game::windowW * percent / 100;
    fixedX = true;
}
void ProjectorComponent::setYToPercentOfWindow(int percent) {
    destRect.y = Game::windowH * percent / 100;
    fixedY = true;
}
void ProjectorComponent::setWidthToPercentOfWindow(int percent) {
    destRect.w = Game::windowW * percent / 100;
    fixedW = true;
}
void ProjectorComponent::setHeightToPercentOfWindow(int percent) {
    destRect.h = Game::windowH * percent / 100;
    fixedH = true;
}
