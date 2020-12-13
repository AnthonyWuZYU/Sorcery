#ifndef RITUAL_H
#define RITUAL_H
#include "card.h"
#include "player.h"

class Player;

class Ritual : public Card {
	int activate_cost;
	int charge;
    public: 
        // Constructor
        Ritual(std::string name, int cost, int activate_cost, int charge, std::string ability="");
 
        // Deconstructor
        ~Ritual();

        //Copy Assignment Operator

        void destroy() override;

        void use_ability() override; 
};
#endif
