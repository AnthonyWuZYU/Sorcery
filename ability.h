#ifndef ABILITY_H
#define ABILITY_H
#include "card.h"
#include <vector>

enum class AbilityType {Triggered, Activated};

class Ability {
    AbilityType type;
    std::string description;

    public:
        Ability(AbilityType type, std::string description);

        ~Ability();

        // activate_ability(): gets called by use_ability(), will perform ability based on the description
        void activate_ability();

        AbilityType get_type();

        std::string get_description();
};


#endif