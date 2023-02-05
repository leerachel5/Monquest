#include "TransformComponent.hpp"
#include "Components.hpp"
#include "OverworldState.hpp"
#include "StateManager.hpp"
#include "Game.hpp"

extern StateManager states;

extern Manager manager;

void TransformComponent::update() {
    Manager* manager = &entity->getManager();
    
    if (states.activeState == "overworld") {
        auto& colliders(manager->getGroup(OverworldState::groupColliders));
        
        for (auto& c : colliders) {
            SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
            
            bool collideN, collideS, collideE, collideW;
            collideN = collideS = collideE = collideW = false;
            
            // Collision from North
            if (velocity.y == -1 && position.y + velocity.y * speed  <= cCol.y + cCol.h && position.y + height * scale >= cCol.y && position.x + width * scale >= cCol.x && position.x <= cCol.x + cCol.w) {
                velocity.y = 0;
                collideN = true;
            }
            // Collision from South
            else if (velocity.y == 1 && (position.y + height * scale) + velocity.y * speed >= cCol.y && position.y <= cCol.y + cCol.h && position.x + width * scale >= cCol.x && position.x <= cCol.x + cCol.w) {
                velocity.y = 0;
                collideS = true;
            }
            // Collision from East
            if (velocity.x == 1 && (position.x + width * scale) + velocity.x * speed >= cCol.x && position.x <= cCol.x + cCol.w && position.y + height * scale >= cCol.y && position.y <= cCol.y + cCol.h) {
                velocity.x = 0;
                collideE = true;
            }
            // Collision from West
            else if (velocity.x == -1 && position.x + velocity.x * speed  <= cCol.x + cCol.w && position.x + width * scale >= cCol.x && position.y + height * scale >= cCol.y && position.y <= cCol.y + cCol.h) {
                velocity.x = 0;
                collideW = true;
            }
            
            // Fix case where collision box is equal in width and height, causing velocity of both x and y to be 0
            if (collideE && (collideN || collideS))
                position.x--;
            else if (collideW && (collideN || collideS))
                position.x++;
        }
    }
    
    position.x += velocity.x * speed;
    position.y += velocity.y * speed;
}
