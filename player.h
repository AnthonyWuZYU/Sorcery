#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include "view.h"
#include "board.h"
#include "minion.h"

class Board;

class Player{
        int life;
        int maxMagic =2;
        int magic;
        std::string name;
        Player *opponent;
        Board *board;

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

        void setOpp( Player *opp); // method to set/change the player's opponent

        Player * getOpp(); // method to return the pointer of the player's opponent

        void setBoard(Board *board); // method to set/change the player's board

        Board * getBoard(); // method to return the player's board

        void draw(); // method to draw a card from the player's deck and add it in the hand

        void play_card(unsigned int i, bool test); // takes index of card from hand to place on field

        void minion_attack(unsigned int i, unsigned int j = 1000); 

        void reset_action();

        void use_abilities();

        void is_dead(unsigned int i, Board* board);
        

};



#endif

