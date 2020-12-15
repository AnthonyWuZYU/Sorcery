#ifndef RITUAL_H
#define RITUAL_H
#include "card.h"
#include "player.h"
#include <vector>

class Player;

class Ritual : public Card{
int activation_cost;
int charges;
Card *target = nullptr;
std::string ability;

public:

// Constructor
Ritual( std::string name, int cost, int activation_cost, int charges, std::string ability = "" );

// Polymorphic Copy Constructor
Ritual( const Card *other );

// Deconstructor
~Ritual();

// method to get the ability
std::string get_ability() const;

// method to return the activation cost
int getActivationCost() const;

// method to return the charges
int getCharges() const;

// method to set/change the charges
void setCharges( int a );

// use the ritual's ability based on the desc. Ability gets used on target (if applicable).
void use_ability( Player *player, std::string desc);

Card* operator=(const Card* other) override;

void print(std::ostream &os) const override;

};

#endif

