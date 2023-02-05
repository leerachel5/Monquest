#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "ECS.hpp"
#include <string>

class ProjectorComponent;


class SpriteComponent : public Component {
public:
    SpriteComponent();
    SpriteComponent(std::string name);
    SpriteComponent(std::string name, std::string id);
    
    ~SpriteComponent();

    void init();

public:
    std::string spriteName;
    std::string facingDirection;
    std::string texID;

private:
    ProjectorComponent* projector;
};

#endif /* SpriteComponent_hpp */
