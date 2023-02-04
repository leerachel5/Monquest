#ifndef PartyComponent_hpp
#define PartyComponent_hpp

#include "ECS.hpp"


class PartyComponent : public Component {
public:
    PartyComponent() {};
    PartyComponent(std::vector<std::string> partyNames) : party{partyNames} {}
    
public:
    std::vector<std::string> party;
};

#endif /* PartyComponent_hpp */
