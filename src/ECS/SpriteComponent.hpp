#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "ECS.hpp"
#include "ProjectorComponent.hpp"
#include "TextureManager.hpp"
#include "TextureComponent.hpp"

class SpriteComponent : public Component {
public:
    SpriteComponent() = default;
    SpriteComponent(std::string name) : spriteName{name} {}
    SpriteComponent(std::string name, std::string id) : spriteName{name}, texID{id} {}
    
    ~SpriteComponent() {}

    void init() override {
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

    void update() override {}

public:
    std::string spriteName;
    std::string facingDirection;
    std::string texID;

private:
    ProjectorComponent* projector;
};

#endif /* SpriteComponent_hpp */
