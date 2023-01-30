#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include "../Game.hpp"
#include "Components.hpp"

class KeyboardController : public Component {
public:
    TransformComponent* transform;
    SpriteComponent* sprite;
    
    void init() override {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }
    
    void update() override {
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
                sprite->Play("WalkNorth");
                sprite->facingDirection = "North";
            }
            idle = false;
        }
        if (currentKeyStates[SDL_SCANCODE_A]) {
            transform->velocity.x = -1;
            if (!(sprite->facingDirection == "North" && currentKeyStates[SDL_SCANCODE_W]) &&
                !(sprite->facingDirection == "South" && currentKeyStates[SDL_SCANCODE_S])) {
                sprite->Play("WalkWest");
                sprite->facingDirection = "West";
            }
            idle = false;
        }
        if (currentKeyStates[SDL_SCANCODE_S]) {
            transform->velocity.y = 1;
            if (!(sprite->facingDirection == "West" && currentKeyStates[SDL_SCANCODE_A]) &&
                !(sprite->facingDirection == "East" && currentKeyStates[SDL_SCANCODE_D])) {
                sprite->Play("WalkSouth");
                sprite->facingDirection = "South";
            }
            idle = false;
        }
        if (currentKeyStates[SDL_SCANCODE_D]) {
            transform->velocity.x = 1;
            if (!(sprite->facingDirection == "North" && currentKeyStates[SDL_SCANCODE_W]) &&
                !(sprite->facingDirection == "South" && currentKeyStates[SDL_SCANCODE_S])) {
                sprite->Play("WalkEast");
                sprite->facingDirection = "East";
            }
            idle = false;
        }
        
        if (idle)
            sprite->Play("Idle" + sprite->facingDirection);
    }
};

#endif /* KeyboardController_hpp */
