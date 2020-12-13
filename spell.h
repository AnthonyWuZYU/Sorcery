#ifndef SPELL_H
#define SPELL_H
#include "card.h"
#include "player.h"

class Player;

class Spell : public Card {
    public: 
        // Constructor
        Spell(std::string name, int cost, std::string ability="");
 
        // Deconstructor
        ~Spell();

        //Copy Assignment Operator

        void destroy() override;

        void use_ability() override; 
};
#endif
