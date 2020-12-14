#include "board.h"
#include <vector>
#include <iostream>
using namespace std;

Board::Board(Deck* deck, Graveyard* graveyard, Hand* hand) : deck{deck}, graveyard{graveyard}, hand{hand} {}

Board::~Board() {}

// Field Operations

void Board::add_to_field(Card* card) {
    if (field.size() < 5 ) {
        field.emplace_back(card);
    }
}

void Board::set_field(std::vector<Card*> new_field) {
    field.assign(new_field.begin(), new_field.end());
}

std::vector<Card*> Board::get_field() const {
    return field;
}

Card* Board::remove_from_field(unsigned int i) {
    Card* temp = field[i];
    field.erase(field.begin()+1);
    return temp;
}

Card* Board::get_card_field(unsigned int i) const {
    return field[i];
}

void Board::set_card_field(unsigned int i, Card* card) {
    field[i] = card;
}

// Hand Operations

Hand* Board::get_hand() const {
    return hand;
}

Card* Board::remove_from_hand(unsigned int i) {
    Card* temp = hand->getCard(i);
    hand->remove(i);
    return temp;
}

Card* Board::get_card_hand(unsigned int i) const {
    return hand->getCard(i);
}

void Board::add_to_hand(Card* card) {
    hand->add(card);
}

// Graveyard Operations

Graveyard* Board::get_graveyard() const{ return graveyard; }

void Board::add_to_graveyard(Card* card) {
    graveyard->add(card);
}

// Deck Operations

Deck * Board::get_deck() const {return deck;}

Card* Board::draw_from_deck() {
    return deck->pop();
}

std::ostream& operator<<(std::ostream &os, const Board &board) {
    for (auto it : board.get_field()) {
        os << it;
    }
    return os;
}

