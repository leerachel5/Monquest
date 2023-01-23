#include "SpriteComponent.hpp"


SpriteComponent::SpriteComponent(const char* texturePath) {
    setTex(texturePath);
}

void SpriteComponent::setTex(const char* texturePath) {
    texture = TextureManager::LoadTexture(texturePath);
}

void SpriteComponent::init() {
    position = &entity->getComponent<PositionComponent>();
    
    srcRect.x = srcRect.y = 0;
    srcRect.w = srcRect.h = 32;
    destRect.w = destRect.h = 64;
}

void SpriteComponent::update() {
    destRect.x = position->x();
    destRect.y = position->y();
}

void SpriteComponent::draw() {
    TextureManager::Draw(texture, srcRect, destRect);
}
