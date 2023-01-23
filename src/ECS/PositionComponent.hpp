#ifndef PositionComponent_hpp
#define PositionComponent_hpp

#include "Components.hpp"

class PositionComponent : public Component {
public:
    PositionComponent()
        : xpos{0}, ypos{0}
    {}

    PositionComponent(int x, int y)
        : xpos{x}, ypos{y}
    {}
    
    inline int x() const { return xpos; }
    
    inline int y() const { return ypos; }

    void init() override {
        xpos = 0;
        ypos = 0;
    }

    void update() override {
        xpos++;
        ypos++;
    }

    void setPos (int x, int y) {
        xpos = x;
        ypos = y;
    }

private:
    int xpos, ypos;
};

#endif /* PositionComponent_hpp */
