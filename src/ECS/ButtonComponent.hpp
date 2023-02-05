#ifndef ButtonComponent_hpp
#define ButtonComponent_hpp

#include "ECS.hpp"

class ProjectorComponent;


class ButtonComponent : public Component {
public:
    ButtonComponent();
    ButtonComponent(void (*f)());
    ~ButtonComponent();
    
    void init() override;
    void update() override;
    
    // Mutator member functions
    void setFunc(void (*f)());
    
public:
    bool isHovering = false;
    void (*func)();
    
private:
    ProjectorComponent* projector;
};


#endif /* ButtonComponent_hpp */
