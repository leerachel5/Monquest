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
            sprite->Play("IdleNorth");
        }
        if (!currentKeyStates[SDL_SCANCODE_A]) {
            transform->velocity.x = 0;
            sprite->Play("IdleWest");
        }
        if (!currentKeyStates[SDL_SCANCODE_S]) {
            transform->velocity.y = 0;
            sprite->Play("IdleSouth");
        }
        if (!currentKeyStates[SDL_SCANCODE_D]) {
            transform->velocity.x = 0;
            sprite->Play("IdleEast");
        }
        
        if (currentKeyStates[SDL_SCANCODE_W]) {
            transform->velocity.y = -1;
            sprite->Play("WalkNorth");
        }
        if (currentKeyStates[SDL_SCANCODE_A]) {
            transform->velocity.x = -1;
            sprite->Play("WalkWest");
        }
        if (currentKeyStates[SDL_SCANCODE_S]) {
            transform->velocity.y = 1;
            sprite->Play("WalkSouth");
        }
        if (currentKeyStates[SDL_SCANCODE_D]) {
            transform->velocity.x = 1;
            sprite->Play("WalkEast");
        }

    }
};

#endif /* KeyboardController_hpp */
