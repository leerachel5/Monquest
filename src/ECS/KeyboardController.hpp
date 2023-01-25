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
            sprite->Play("WalkNorth");
            sprite->direction = "North";
            idle = false;
        }
        if (currentKeyStates[SDL_SCANCODE_A]) {
            transform->velocity.x = -1;
            sprite->Play("WalkWest");
            sprite->direction = "West";
            idle = false;
        }
        if (currentKeyStates[SDL_SCANCODE_S]) {
            transform->velocity.y = 1;
            sprite->Play("WalkSouth");
            sprite->direction = "South";
            idle = false;
        }
        if (currentKeyStates[SDL_SCANCODE_D]) {
            transform->velocity.x = 1;
            sprite->Play("WalkEast");
            sprite->direction = "East";
            idle = false;
        }
        
        if (idle)
            sprite->Play("Idle" + sprite->direction);
    }
};

#endif /* KeyboardController_hpp */
