#include "SpriteComponent.hpp"
#include "ProjectorComponent.hpp"
#include "TextureComponent.hpp"

SpriteComponent::SpriteComponent() {}

SpriteComponent::SpriteComponent(std::string name) : spriteName{name} {}

SpriteComponent::SpriteComponent(std::string name, std::string id) : spriteName{name}, texID{id} {}

SpriteComponent::~SpriteComponent() {}

void SpriteComponent::init() {
    if (!entity->hasComponent<TextureComponent>())
        entity->addComponent<TextureComponent>(texID);
    
    projector = &entity->getComponent<ProjectorComponent>();
    
    projector->AddAnimation("IdleSouth", 0, 1, 100);
    projector->AddAnimation("WalkSouth", 1, 4, 100);
    projector->AddAnimation("IdleWest", 2, 1, 100);
    projector->AddAnimation("WalkWest", 3, 4, 100);
    projector->AddAnimation("IdleEast", 4, 1, 100);
    projector->AddAnimation("WalkEast", 5, 4, 100);
    projector->AddAnimation("IdleNorth", 6, 1, 100);
    projector->AddAnimation("WalkNorth", 7, 4, 100);
    
    projector->PlayAnimation("IdleSouth");
    
    facingDirection = "South";
}
