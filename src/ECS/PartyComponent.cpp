#include "PartyComponent.hpp"
#include "SpriteComponent.hpp"
//#include "Game.hpp"

extern CreatureManager* creatures;

PartyComponent::PartyComponent() {}

PartyComponent::PartyComponent(std::vector<Creature> partyCreatures) {
    for (Creature c : partyCreatures) {
        CreatureID creatureID = addCreature(c.name, c.level, c.health, c.maxHealth, c.gender);
        party.push_back(creatureID);
    }
}

CreatureID PartyComponent::addCreature(std::string name, int level, int health, int maxHealth, Gender gender) {
    Creature* newCreature = new Creature(name, level, health, maxHealth, gender);
    CreatureID creatureID = creatures->addCreature(entity->getComponent<SpriteComponent>().spriteName, newCreature);
    party.push_back(creatureID);
    
    return creatureID;
}
