#include "board.h"

Board::Board(Deck deck, Graveyard graveyard, Hand hand) : deck{&deck}, graveyard{&graveyard}, hand{&hand} {}

Board::~Board() {}

void Board::play_card(Card card) {
    if (cards_in_play.size() < 5 ) {
        cards_in_play.emplace_back(card);
    }
}