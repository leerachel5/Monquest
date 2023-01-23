#include "SpriteComponent.hpp"


SpriteComponent::SpriteComponent(const char* texturePath) {
    setTex(texturePath);
}

void SpriteComponent::setTex(const char* texturePath) {
    texture = TextureManager::LoadTexture(texturePath);
}

void SpriteComponent::init() {
    transform = &entity->getComponent<TransformComponent>();
    
    srcRect.x = srcRect.y = 0;
    srcRect.w = srcRect.h = 32;
    destRect.w = destRect.h = 64;
}

void SpriteComponent::update() {
    destRect.x = (int)transform->position.x;
    destRect.y = (int)transform->position.y;
}

void SpriteComponent::draw() {
    TextureManager::Draw(texture, srcRect, destRect);
}
