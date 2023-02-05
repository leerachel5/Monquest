#ifndef PartyComponent_hpp
#define PartyComponent_hpp

#include "ECS.hpp"
#include "Creature.hpp"

using CreatureID = std::size_t;


class PartyComponent : public Component {
public:
    PartyComponent();
    PartyComponent(std::vector<Creature> partyCreatures);
    
    CreatureID addCreature(std::string name, int level, int health, int maxHealth, Gender gender);
    
public:
    std::vector<CreatureID> party;
};

#endif /* PartyComponent_hpp */
