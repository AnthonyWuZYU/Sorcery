#ifndef BOARD_H
#define BOARD_H

#include "deck.h"
#include "graveyard.h"
#include "hand.h"
#include <vector>
#include <iostream>

class Deck;
class Hand;

class Board {
    Deck *deck;
    Graveyard *graveyard;
    std::vector<Card*> field;
    Hand *hand; 
    Card *ritual = nullptr;

    public: 
        Board(Deck *deck, Graveyard *graveyard, Hand *hand);
        ~Board();

        Card* get_ritual() const;

        void set_ritual( Card* a );

        //Field Operations

        void set_field(std::vector<Card*> new_field);

        std::vector<Card*> get_field() const;

        Card* remove_from_field(unsigned int i);

        void add_to_field(Card* card);

        void set_card_field(unsigned int i, Card* card);

        Card* get_card_field(unsigned int i) const;

        // Deck Operations

        Deck* get_deck() const;
        
        void set_deck(Deck* d);
        
        Card* draw_from_deck();

        // Hand Operations
        
        Hand* get_hand() const;

        Card* remove_from_hand(unsigned int i);
        
        Card* get_card_hand(unsigned int i) const;
        
        void add_to_hand(Card* card);

        // Graveyard Operations

        Card* remove_from_graveyard();

        Graveyard* get_graveyard() const;

        void add_to_graveyard(Card* card);

        void destroy( Card* card );


};
std::ostream& operator<<(std::ostream &os, const Board &board);
#endif
