#include "board.h"

Board::Board(Deck deck, Graveyard graveyard, Hand hand) : deck{&deck}, graveyard{&graveyard}, hand{&hand} {}

Board::~Board() {}

void Board::move_to_field(Card card) {
    if (cards_in_play.size() < 5 ) {
        cards_in_play.emplace_back(card);
    }
}

void remove_from_play(unsigned int i {
    
}

Card remove_from_hand(unsigned int i) {

}

Card draw_from_deck() {
    return deck->pop();
}

