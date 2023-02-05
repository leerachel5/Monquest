#ifndef LinkComponent_hpp
#define LinkComponent_hpp

#include "ECS.hpp"


class LinkComponent : public Component {
public:
    LinkComponent(std::string dMap, int dX, int dY);

public:
    std::string destMap;
    int destX, destY;
};

#endif /* LinkComponent_hpp */
