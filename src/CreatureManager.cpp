#include "CreatureManager.hpp"
#include "ECS/Creature.hpp"


CreatureManager::CreatureManager() {}

CreatureManager::~CreatureManager() {}

Creature* CreatureManager::getCreature(std::string playerName, CreatureID creatureID) {
    return creatureMap.at(playerName).at(creatureID);
}

CreatureID CreatureManager::addCreature(std::string playerName, Creature* creature) {
    std::unordered_map<CreatureID, Creature*> newCreature;

    if (!creatureMap.contains(playerName)) {
        std::unordered_map<CreatureID, Creature*> newCreature;
        creatureMap.insert({playerName, newCreature});
    }
    creatureMap[playerName].insert({uniqueCreatureID, creature});

    return uniqueCreatureID++;
}

void CreatureManager::removeCreature(std::string playerName, CreatureID creatureID) {
    creatureMap.at(playerName).erase(creatureID);
}
