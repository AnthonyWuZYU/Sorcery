#include "board.h"

Board::Board(Deck deck, Graveyard graveyard, Hand hand) : deck{&deck}, graveyard{&graveyard}, hand{&hand} {}

Board::~Board() {}

void Board::move_to_field(Card card) {
    if (cards_in_play.size() < 5 ) {
        cards_in_play.emplace_back(card);
    }
}

void set_field(vector<Card> new_field) {
    field.assign(new_field.begin(), new_field.end());
}

vector<Card> get_field() {
    return field;
}

Card draw_from_deck() {
    return deck->pop();
}

Card remove_from_field(unsigned int i) {
    Card temp = field(i);
    field.erase(i);
    return temp;
}

Card remove_from_hand(unsigned int i) {
    Card temp = hand->getCard(i);
    hand->remove(i);
    return temp;
}

Card get_card_field(unsigned int i) {
    return field[i];
}

void set_card_field(unsigned int i, Card card) {
    field[i] = card;
}

void move_to_graveyard(Card card) {
    graveyard->add(card);
}

void move_to_hand(Card card) {
    hand->add(card);
}



