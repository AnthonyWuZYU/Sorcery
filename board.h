#ifndef BOARD_H
#define BOARD_H

#include "deck.h"
#include "graveyard.h"
#include "hand.h"
#include <vector>

class Board {
    Deck *deck;
    Graveyard *graveyard;
    std::vector<Card> cards_in_play;
    Hand *hand; 

    public: 
        Board(Deck deck, Graveyard graveyard, Hand hand);
        ~Board();
        void play_card(Card card);
};

#endif