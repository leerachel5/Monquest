#ifndef TransformComponent_hpp
#define TransformComponent_hpp

#include "ECS.hpp"
#include "../Vector2D.hpp"
#include <SDL2/SDL.h>


class TransformComponent : public Component {
public:
    Vector2D position;
    Vector2D velocity;
    
    int height = 32;
    int width = 32;
    int scale = 1;
    
    int speed = 3;

public:
    TransformComponent() {
        position.Zero();
    }
    
    TransformComponent(int sc)
        : scale{sc}
    {
        position.x = 500;
        position.y = 300;
    }

    TransformComponent(float x, float y)
        : position{Vector2D(x, y)}
    {}
    
    TransformComponent(float x, float y, int w, int h, int sc)
        : position{Vector2D(x, y)}, width{w}, height{h}, scale{sc}
    {}
    
    void init() override {
        velocity.Zero();
    }
    
    void update() override;
    
    SDL_Rect toRect() {
        SDL_Rect rect = {static_cast<int>(position.x), static_cast<int>(position.y), width * scale, height * scale};
        return rect;
    }
};

#endif /* TransformComponent_hpp */
