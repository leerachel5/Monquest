#ifndef TransformComponent_hpp
#define TransformComponent_hpp

#include "Components.hpp"
#include "../Vector2D.hpp"

class TransformComponent : public Component {
public:
    Vector2D position;
    Vector2D velocity;
    
    int speed = 3;

public:
    TransformComponent()
        : position{Vector2D()}
    {}

    TransformComponent(int x, int y)
        : position{Vector2D(x, y)}
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
