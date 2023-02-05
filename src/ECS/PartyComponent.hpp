#ifndef PartyComponent_hpp
#define PartyComponent_hpp

#include "ECS.hpp"
#include "CreatureManager.hpp"


class PartyComponent : public Component {
public:
    PartyComponent();
    PartyComponent(std::vector<Creature> partyCreatures);
    
    CreatureID addCreature(std::string name, int level, int health, int maxHealth, Gender gender);
    
public:
    std::vector<CreatureID> party;
};

#endif /* PartyComponent_hpp */
