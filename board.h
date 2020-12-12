#ifndef BOARD_H
#define BOARD_H

#include "deck.h"
#include "graveyard.h"
#include "hand.h"
#include <vector>

class Deck;

class Board {
    Deck *deck;
    Graveyard *graveyard;
    std::vector<Card> field;
    Hand *hand; 

    public: 
        Board(Deck deck, Graveyard graveyard, Hand hand);
        ~Board();
        void move_to_field(Card card);
        Card draw_from_deck();
        Card remove_from_field(unsigned int i);
        Card remove_from_hand(unsigned int i);
        Card get_card_field(unsigned int i);
        void set_card_field(unsigned int i);
        void move_to_graveyard(Card card);
        void move_to_hand(Card card);

};

#endif