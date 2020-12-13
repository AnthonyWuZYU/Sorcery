#ifndef ENCHANT_H
#define ENCHANT_H
#include "card.h"
#include "player.h"
#include <vector>

class Player;

class Enchant : public Card {
    int addAtk;
    int addDef;
    int mulAtk;
    int mulDef;

    public: 
        // Constructor
        Enchant(std::string name, int cost, int addAtk, int addDef, int mulAtk, int mulDef, std::string ability="");
 
        // Deconstructor
        ~Enchant();

        //Copy Assignment Operator

        //use_ability(): uses the ability object of the card to perform the ability
        //void use_ability() override;
	
	int get_addAtk();

	int get_addDef();

        //destroy(): destroys the card
        void destroy() override;

        void use_ability() override; 
};
#endif
