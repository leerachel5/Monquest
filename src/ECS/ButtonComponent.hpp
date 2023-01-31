#ifndef ButtonComponent_hpp
#define ButtonComponent_hpp

#include "ECS.hpp"
#include "ColliderComponent.hpp"
#include "../Collision.hpp"

class ButtonComponent : public Component {
public:
    ButtonComponent() {}
    ~ButtonComponent() {}
    
    void update() override {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_Rect mouse = {mouseX, mouseY, 1, 1};
        
        if (Collision::AABB(mouse, entity->getComponent<TransformComponent>().toRect())) {
            isHovering = true;
        } else {
            isHovering = false;
        }
    }
    void draw() override {}

public:
    bool isHovering = false;
};

#endif /* ButtonComponent_hpp */
