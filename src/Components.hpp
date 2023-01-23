/*
 Temporary file containing various component classes.
 
 To do: Separate component classes into own files.
 */

#ifndef Components_hpp
#define Components_hpp

#include "ECS.hpp"

class PositionComponent : public Component {
public:
    inline int x() const { return xpos; };
    inline int y() const { return ypos; };
    
    void init() override {
        xpos = 0;
        ypos = 0;
    }
    
    void update() override {
        xpos++;
        ypos++;
    }
    
    void setPos(int x, int y) {
        xpos = x;
        ypos = y;
    }

private:
    int xpos, ypos;
};

#endif /* Components_hpp */
