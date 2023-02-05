#ifndef ProjectorComponent_hpp
#define ProjectorComponent_hpp

#include "ECS.hpp"
#include "Animation.hpp"
#include <unordered_map>
#include <SDL2/SDL.h>

class TransformComponent;


class ProjectorComponent : public Component {
public:
    ProjectorComponent();
    ProjectorComponent(bool isAnimated);
    ~ProjectorComponent();
    
    // Main loop functions
    void init() override;
    void update() override;
    
    // Animations
    void AddAnimation(std::string animName, int index, int frames, int speed);
    void PlayAnimation(std::string animName);
    void ToggleAnimation(bool flag);
    
    // Mutator member functions
    void setXToPercentOfWindow(int percent);
    void setYToPercentOfWindow(int percent);
    void setWidthToPercentOfWindow(int percent);
    void setHeightToPercentOfWindow(int percent);
    
    
public:
    SDL_Rect srcRect, destRect;

private:
    TransformComponent* transform;
    
    bool animated = false;
    int animIndex = 0;
    int frames = 0;
    int speed = 0;
    std::unordered_map<std::string, Animation> animations;
    
    // When true, projection is independent of the entity's TransformComponent
    bool fixedX = false;
    bool fixedY = false;
    bool fixedW = false;
    bool fixedH = false;
};

#endif /* ProjectorComponent_hpp */
