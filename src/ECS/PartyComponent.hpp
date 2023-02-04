#ifndef PartyComponent_hpp
#define PartyComponent_hpp

#include "ECS.hpp"
#include "Creature.hpp"


class PartyComponent : public Component {
public:
    PartyComponent() {};
    PartyComponent(std::vector<Creature> partyCreatures) : creatures{partyCreatures} {}
    
    void addCreature(std::string name, int level, int health, int maxHealth, Gender gender) {
        creatures.push_back(Creature(name, level, health, maxHealth, gender));
    }
    
public:
    std::vector<Creature> creatures;
};

#endif /* PartyComponent_hpp */
