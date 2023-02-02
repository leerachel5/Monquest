#ifndef MouseController_hpp
#define MouseController_hpp

#include "ECS.hpp"
#include "../Collision.hpp"


class MouseController : public Component {
public:
    MouseController() {}
    ~MouseController() {}
    
    void init() override {
        isHovering = false;
    }
    
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

public:
    bool isHovering;
};

#endif /* MouseController_hpp */
