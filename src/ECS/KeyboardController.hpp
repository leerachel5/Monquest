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
        if (Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym) {
                case SDLK_w:
                    transform->velocity.y = -1;
                    sprite->Play("WalkNorth");
                    break;
                case SDLK_a:
                    transform->velocity.x = -1;
                    sprite->Play("WalkWest");
                    break;
                case SDLK_s:
                    transform->velocity.y = 1;
                    sprite->Play("WalkSouth");
                    break;
                case SDLK_d:
                    transform->velocity.x = 1;
                    sprite->Play("WalkEast");
                    break;
                
                default:
                    break;
            }
        }
        if (Game::event.type == SDL_KEYUP) {
            switch (Game::event.key.keysym.sym) {
                case SDLK_w:
                    transform->velocity.y = 0;
                    sprite->Play("IdleNorth");
                    break;
                case SDLK_a:
                    transform->velocity.x = 0;
                    sprite->Play("IdleWest");
                    break;
                case SDLK_s:
                    transform->velocity.y = 0;
                    sprite->Play("IdleSouth");
                    break;
                case SDLK_d:
                    transform->velocity.x = 0;
                    sprite->Play("IdleEast");
                    break;
                case SDLK_ESCAPE:
                    Game::isRunning = false;
                    break;
                
                default:
                    break;
            }
        }
    }
};

#endif /* KeyboardController_hpp */
