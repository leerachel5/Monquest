#include "TransformComponent.hpp"
#include "Components.hpp"

void TransformComponent::update() {
    auto& colliders(manager.getGroup(Game::groupColliders));
    
    for (auto& c : colliders) {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        
        // Collision from North
        if (velocity.y == -1 && position.y + velocity.y * speed  <= cCol.y + cCol.h && position.y + height * scale >= cCol.y && position.x + width * scale >= cCol.x && position.x <= cCol.x + cCol.w) {
            velocity.y = 0;
        }
        // Collision from South
        else if (velocity.y == 1 && (position.y + height * scale) + velocity.y * speed >= cCol.y && position.y <= cCol.y + cCol.h && position.x + width * scale >= cCol.x && position.x <= cCol.x + cCol.w) {
            velocity.y = 0;
        }
        // Collision from East
        if (velocity.x == 1 && (position.x + width * scale) + velocity.x * speed >= cCol.x && position.x <= cCol.x + cCol.w && position.y + height * scale >= cCol.y && position.y <= cCol.y + cCol.h) {
            velocity.x = 0;
        }
        // Collision from West
        else if (velocity.x == -1 && position.x + velocity.x * speed  <= cCol.x + cCol.w && position.x + width * scale >= cCol.x && position.y + height * scale >= cCol.y && position.y <= cCol.y + cCol.h) {
            velocity.x = 0;
        }
    }
    position.x += velocity.x * speed;
    position.y += velocity.y * speed;
}
