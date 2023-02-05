#ifndef CreatureManager_hpp
#define CreatureManager_hpp

#include "ECS/Creature.hpp"
#include <unordered_map>

using CreatureID = std::size_t;

class CreatureManager {
public:
    CreatureManager();
    ~CreatureManager();
    
    // Accessor Methods
    Creature* getCreature(std::string playerName, std::size_t creatureID);
    
    // Mutator Methods
    CreatureID addCreature(std::string playerName, Creature* creature);
    void removeCreature(std::string playerName, CreatureID creatureID);
    
    
private:
    CreatureID uniqueCreatureID = 0;
    
    // Outer map key is player name, outer map value is the inner map containing
    // the CreatureID as the key and a pointer to the Creature as a value
    std::unordered_map<std::string, std::unordered_map<CreatureID, Creature*>> creatureMap;
};


#endif /* CreatureManager_hpp */
