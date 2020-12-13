#include "board.h"
#include <vector>
#include <iostream>
using namespace std;

Board::Board(Deck* deck, Graveyard* graveyard, Hand* hand) : deck{deck}, graveyard{graveyard}, hand{hand} {}

Board::~Board() {}

void Board::move_to_field(Card card) {
    if (field.size() < 5 ) {
        field.emplace_back(card);
    }
}

void Board::set_field(std::vector<Card> new_field) {
    field.assign(new_field.begin(), new_field.end());
}

std::vector<Card> Board::get_field() {
    return field;
}

Card Board::draw_from_deck() {
    return deck->pop();
}

Card Board::remove_from_field(unsigned int i) {
    Card temp = field[i];
    field.erase(field.begin()+1);
    return temp;
}

Card Board::remove_from_hand(unsigned int i) {
    Card temp = hand->getCard(i);
    hand->remove(i);
    return temp;
}

Card Board::get_card_hand(unsigned int i) {
    return hand->getCard(i);
}

Card Board::get_card_field(unsigned int i) {
    return field[i];
}

void Board::set_card_field(unsigned int i, Card card) {
    field[i] = card;
}

void Board::move_to_graveyard(Card card) {
    graveyard->add(card);
}

void Board::move_to_hand(Card card) {
    hand->add(card);
}



