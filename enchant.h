#ifndef ENCHANT_H
#define ENCHANT_H
#include "card.h"
#include "player.h"
#include <vector>

class Player;

class Enchant : public Card {
    int addAtk;
    int addDef;

    public: 
        // Constructor
        Enchant(std::string name, int cost, int addAtk, int addDef, std::string ability="");

        // Deconstructor
        ~Enchant();

        //Copy Assignment Operator
        Card * operator=(const Card* other) override;

        //use_ability(): uses the ability object of the card to perform the ability
        //void use_ability() override;
	
	int get_addAtk();

	int get_addDef();

        //destroy(): destroys the card
        void destroy() override;

        void use_ability(); 
        void print(std::ostream &os) const override; 
};

#endif