#ifndef ColliderComponent_hpp
#define ColliderComponent_hpp

#include "ECS.hpp"
#include <string>
#include <SDL2/SDL.h>

class TransformComponent;


class ColliderComponent : public Component {
public:
    ColliderComponent(std::string t);
    ColliderComponent(std::string t, int xpos, int ypos, int size);
    
    void init() override;
    void update() override;
    void draw() override;

public:
    SDL_Rect collider;
    std::string tag;
    
    SDL_Texture* tex;
    SDL_Rect srcRect, destRect;
    
    TransformComponent* transform;
};

#endif /* ColliderComponent_hpp */
