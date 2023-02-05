#include "ColliderComponent.hpp"
#include "../Game.hpp"
#include "../TextureManager.hpp"
#include "TransformComponent.hpp"


ColliderComponent::ColliderComponent(std::string t) : tag{t} {}

ColliderComponent::ColliderComponent(std::string t, int xpos, int ypos, int size) {
    tag = t;
    collider.x = xpos;
    collider.y = ypos;
    collider.w = collider.h = size;
}

void ColliderComponent::init() {
    if (!entity->hasComponent<TransformComponent>())
        entity->addComponent<TransformComponent>();
    
    transform = &entity->getComponent<TransformComponent>();

    tex = TextureManager::LoadTexture("assets/colTex.png");
    
    srcRect = {0, 0, 32, 32};
    destRect = {collider.x, collider.y, collider.w, collider.h};
    
}

void ColliderComponent::update() {
    if (tag != "terrain") {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
    }
    
    destRect.x = collider.x - Game::camera.x;
    destRect.y = collider.y - Game::camera.y;
}

void ColliderComponent::draw() {
    TextureManager::Draw(tex, &srcRect, &destRect);
}
