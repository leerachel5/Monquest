#ifndef TransformComponent_hpp
#define TransformComponent_hpp

#include "Components.hpp"
#include "../Vector2D.hpp"

class TransformComponent : public Component {
public:
    Vector2D position;
    Vector2D velocity;
    
    int height = 26;
    int width = 11;
    int scale = 1;
    
    int speed = 3;

public:
    TransformComponent()
        : position{Vector2D()}
    {}
    
    TransformComponent(int sc)
        : position{Vector2D()}, scale{sc}
    {}

    TransformComponent(float x, float y)
        : position{Vector2D(x, y)}
    {}
    
    TransformComponent(float x, float y, int h, int w, int sc)
        : position{Vector2D(x, y)}, height{h}, width{w}, scale{sc}
    {}
    
    void init() override {
        velocity.x = velocity.y = 0;
    }
    
    void update() override {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;   
    }
};

#endif /* TransformComponent_hpp */
