#ifndef KeyboardController_hpp
#define KeyboardController_hpp

#include "ECS.hpp"

class TransformComponent;
class SpriteComponent;
class ProjectorComponent;


class KeyboardController : public Component {
public:
    void init() override;
    void update() override;
    
public:
    TransformComponent* transform;
    SpriteComponent* sprite;
    ProjectorComponent* projector;
};

#endif /* KeyboardController_hpp */
