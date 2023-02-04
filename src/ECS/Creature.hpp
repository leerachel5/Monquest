#ifndef Creature_hpp
#define Creature_hpp

#include <string>

enum genderTypes : std::size_t {
    male,
    female
};

using Gender = std::size_t;

struct Creature {
    std::string name;
    int level;
    int health;
    int maxHealth;
    Gender gender;
    
    Creature(std::string nm, int lvl, int hp, int maxHp, Gender gndr) : name{nm}, level{lvl}, health{hp}, maxHealth{maxHp}, gender{gndr} {}
};


#endif /* Creature_hpp */
