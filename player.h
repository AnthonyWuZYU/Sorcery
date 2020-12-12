#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include "hand.h"
#include "deck.h"
#include "view.h"

class Deck;
class Hand;

class Player{
        int life;
        int maxMagic;
        int magic;
        std::string name;
        Deck *deck;
        Hand *hand;
        Player *opponent;

    public:
        Player(); // Player default constructor

        Player( std::string name ); // Constructor that initializes using player's name

        virtual ~Player(); // Player destructor

        int getLife(); // method that returns player's life

        void setLife( int life ); // method to change player's life

        int getMagic(); // method that returns player's magic value

        void setMagic( int magic ); // method to change player's magic value

        int getMaxMagic(); // method that returns player's max magic value

        void addMaxMagic( int magic ); // method to change player's max magic value

        std::string getName(); // method that returns player's name

        void setName( std::string name ); // method to change player's name

        Deck *getDeck(); // method that returns player's deck

        Hand *getHand(); // method that returns player's hand

        void setDeck( Deck *deck ); // method to set/change the player's deck

        void setHand( Hand *hand ); // method to set/change the player's hand

        void setOpp( Player *opp); // method to set/change the player's opponent

        Player * getOpp(); // method to return the pointer of the player's opponent

        void draw(); // method to draw a card from the player's deck and add it in the hand
};

#endif
