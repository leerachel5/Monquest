#include "ButtonComponent.hpp"
#include "../Collision.hpp"
#include "ProjectorComponent.hpp"

ButtonComponent::ButtonComponent() : func{[](){}} {}

ButtonComponent::ButtonComponent(void (*f)()) : func{f} {}

ButtonComponent::~ButtonComponent() {}

void ButtonComponent::init() {
    projector = &entity->getComponent<ProjectorComponent>();
}

void ButtonComponent::update() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect mouse = {mouseX, mouseY, 1, 1};
    
    isHovering = Collision::AABB(mouse, projector->destRect);
    
    if (isHovering)
        projector->PlayAnimation("hover");
    else
        projector->PlayAnimation("default");
}

void ButtonComponent::setFunc(void (*f)()) {
    func = f;
}
