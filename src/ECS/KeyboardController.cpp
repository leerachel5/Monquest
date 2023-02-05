#include "KeyboardController.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "ProjectorComponent.hpp"
#include <SDL2/SDL.h>


void KeyboardController::init() {
    transform = &entity->getComponent<TransformComponent>();
    sprite = &entity->getComponent<SpriteComponent>();
    projector = &entity->getComponent<ProjectorComponent>();
}

void KeyboardController::update() {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    
    if (!currentKeyStates[SDL_SCANCODE_W]) {
        transform->velocity.y = 0;
    }
    if (!currentKeyStates[SDL_SCANCODE_A]) {
        transform->velocity.x = 0;
    }
    if (!currentKeyStates[SDL_SCANCODE_S]) {
        transform->velocity.y = 0;
    }
    if (!currentKeyStates[SDL_SCANCODE_D]) {
        transform->velocity.x = 0;
    }
    
    bool idle = true;
    if (currentKeyStates[SDL_SCANCODE_W]) {
        transform->velocity.y = -1;
        if (!(sprite->facingDirection == "West" && currentKeyStates[SDL_SCANCODE_A]) &&
            !(sprite->facingDirection == "East" && currentKeyStates[SDL_SCANCODE_D])) {
            projector->PlayAnimation("WalkNorth");
            sprite->facingDirection = "North";
        }
        idle = false;
    }
    if (currentKeyStates[SDL_SCANCODE_A]) {
        transform->velocity.x = -1;
        if (!(sprite->facingDirection == "North" && currentKeyStates[SDL_SCANCODE_W]) &&
            !(sprite->facingDirection == "South" && currentKeyStates[SDL_SCANCODE_S])) {
            projector->PlayAnimation("WalkWest");
            sprite->facingDirection = "West";
        }
        idle = false;
    }
    if (currentKeyStates[SDL_SCANCODE_S]) {
        transform->velocity.y = 1;
        if (!(sprite->facingDirection == "West" && currentKeyStates[SDL_SCANCODE_A]) &&
            !(sprite->facingDirection == "East" && currentKeyStates[SDL_SCANCODE_D])) {
            projector->PlayAnimation("WalkSouth");
            sprite->facingDirection = "South";
        }
        idle = false;
    }
    if (currentKeyStates[SDL_SCANCODE_D]) {
        transform->velocity.x = 1;
        if (!(sprite->facingDirection == "North" && currentKeyStates[SDL_SCANCODE_W]) &&
            !(sprite->facingDirection == "South" && currentKeyStates[SDL_SCANCODE_S])) {
            projector->PlayAnimation("WalkEast");
            sprite->facingDirection = "East";
        }
        idle = false;
    }
    
    if (idle)
        projector->PlayAnimation("Idle" + sprite->facingDirection);
}
