#include "ability.h"
using namespace std;

Ability::Ability(AbilityType type, std::string description) : type{type}, description{description} {}

void Ability::activate_ability() {

        // Minion Abilities : Activated
        if (description == "Deals damage to all the opponent minions equal to its attack value when it dies") {

        } else if (description == "Whenever an opponent's minion enters play, deal 1 damage to it") {

        } else if (description == "At the end of your turn, all your minions gain +0/+1") {

        } 
        // Minion Abilities : Triggered
        else if (description == "1 | Deal 1 damage to target minion") {

        } else if (description == "Summon a 1/1 air elemental") {

        } else if (description == "Summon up to three 1/1 air elementals") {

        }
        // Rituals
        else if (description == "At the start of your turn, gain 1 magic") {

        } else if (desription == "1 | Whenever a minion enters play under your control, it gains +1/+1") {

        } else if (description == "Whenever a minion enters play, destroy it") {

        }
        // Spells 
        else if (description == "Destroy target minion or ritual") {

        } else if (description == "Return target minion to its owner's hand") {

        } else if (description == "Your ritual gains 3 charges") {

        } else if (description == "Destroy the top enchant on target minion") {

        } else if (description == "Resurrect the top minion in your graveyard and set its defence to 1") {

        } else if (description == "Deal 2 damage to all minions") {

        }
    }
}

AbilityType Ability::get_type(){return type;}

std::string Ability::get_description() {return description;}

