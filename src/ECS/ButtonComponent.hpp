#ifndef ButtonComponent_hpp
#define ButtonComponent_hpp

#include "ECS.hpp"
#include "../Collision.hpp"


class ButtonComponent : public Component {
public:
    ButtonComponent() : func{[](){}} {}
    ButtonComponent(void (*f)()) : func{f} {}
    ~ButtonComponent() {}
    
    void init() override {
        projector = &entity->getComponent<ProjectorComponent>();
    }
    
    void update() override {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_Rect mouse = {mouseX, mouseY, 1, 1};
        
        isHovering = Collision::AABB(mouse, projector->destRect);
    }
    
    // Mutator member functions
    void setFunc(void (*f)()) {
        func = f;
    }
    
public:
    bool isHovering = false;
    void (*func)();
    
private:
    ProjectorComponent* projector;
};


#endif /* ButtonComponent_hpp */
