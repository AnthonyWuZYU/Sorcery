#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include "view.h"
#include "hand.h"
#include "deck.h"

class Player{
int life;
int magic;
std::string name;
Deck *deck;
Hand *hand;

public:
Player(); // Player default constructor
Player( std::string name ); // Constructor that initializes using player's name
virtual ~Player(); // Player destructor
int getLife(); // method that returns player's life
void setLife( int life ); // method to change player's life
int getMagic(); // method that returns player's magic value
void setMagic( int magic ); // method to change player's magic value
std::string getName(); // method that returns player's name
void setName( std::string name ); // method to change player's name
Deck getDeck(); // method that returns player's deck
Hand getHand(); // method that returns player's hand
void setDeck( Deck *deck ); // method to set/change the player's deck
void setHand( Hand *hand ); // method to set/change the player's hand
};

#endif
