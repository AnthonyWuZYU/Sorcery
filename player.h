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
Player(int life = 20, int magic = 0); // Player default constructor
virtual ~Player(); // Player destructor
int getLife(); // method that returns player's life
void setLife(); // method to change player's life
int getMagic(); // method that returns player's magic value
int setMagic(); // method to change player's magic value
std::string getName(); // method that returns player's name
void setName(); // method to change player's name
Deck getDeck(); // method that returns player's deck
Hand getHand(); // method that returns player's hand
};

#endif
