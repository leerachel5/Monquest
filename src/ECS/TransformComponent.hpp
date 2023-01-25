#ifndef TransformComponent_hpp
#define TransformComponent_hpp

#include "Components.hpp"
#include "../Vector2D.hpp"

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
    
    TransformComponent(float x, float y, int h, int w, int sc)
        : position{Vector2D(x, y)}, height{h}, width{w}, scale{sc}
    {}
    
    void init() override {
        velocity.Zero();
    }
    
    void update() override {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};

#endif /* TransformComponent_hpp */
