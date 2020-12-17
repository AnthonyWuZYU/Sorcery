#include "board.h"
#include <vector>
#include <iostream>
using namespace std;

Board::Board(Deck* deck, Graveyard* graveyard, Hand* hand) : deck{deck}, graveyard{graveyard}, hand{hand} {}

Board::~Board() {
	for (auto& it : field) {
                delete it;
        }
	field.clear();
}

// Field Operations

void Board::add_to_field(Player* player, Card* card) {
    if (field.size() < 5 ) {
        field.emplace_back(card);
	player->getBoard()->trigger(player, "enter");
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
    field.erase(field.begin()+i);
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

Card* Board::remove_from_graveyard(){
    return graveyard->revive();
}

// Deck Operations

Deck * Board::get_deck() const {return deck;}

void Board::set_deck(Deck* d) {deck = d;}

Card* Board::draw_from_deck() {
    return deck->pop();
}

Card* Board::get_ritual() const {return ritual;}

void Board::set_ritual( Card* a ){
    // Remove the current ritual from play

    // Set the new the ritual
    ritual = a;
}

std::ostream& operator<<(std::ostream &os, const Board &board) {
    vector<vector<string>> cards_graphics;
    for (auto it : board.get_field()) {
        Minion *temp = dynamic_cast<Minion *>(it);
        string ability = temp->get_ability();
        if (ability == " ") {
            cards_graphics.emplace_back(display_minion_no_ability(temp->get_name(),temp->get_cost(),temp->get_attack(),temp->get_defence()));
        } else if (temp->get_activate_cost() == 0) {
                cards_graphics.emplace_back(display_minion_triggered_ability(temp->get_name(),temp->get_cost(),
                                          temp->get_attack(),temp->get_defence(), temp->get_ability()));

        } else {
                cards_graphics.emplace_back(display_minion_activated_ability(temp->get_name(),temp->get_cost(),
                                          temp->get_attack(),temp->get_defence(), temp->get_activate_cost(), temp->get_ability()));
        }
    }



    // If we don't have 5 cards in play
    if (cards_graphics.size() != 5) {
        int diff = 5 - cards_graphics.size();
        for (int i = 0; i < diff; i++) {
            cards_graphics.emplace_back(CARD_TEMPLATE_BORDER);
        }
    }

    for (int i = 0; i < 11; i++) {
        os << EXTERNAL_BORDER_CHAR_UP_DOWN;
        for (auto it: cards_graphics) {
            os << it[i];
        }
        os << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
    }
    return os;
}

void Board::destroy( Card* card ){
    delete card;
}

void Board::trigger( Player *player, string type ) {
	if ( type == "start") {
		if ( this->get_ritual() != nullptr ) {
			if ( this->get_ritual()->get_name() == "Dark Ritual" ) {
				Ritual* temp = dynamic_cast<Ritual*>(this->get_ritual());	
				temp->use_ability(player, temp->get_ability());
                                temp = nullptr;
                                delete temp;		
			}
		}

	} else if ( type == "end" ) {
		for (auto it: this->get_field()) {
			if (it->get_name() == "Potion Seller" ) {
				Minion *temp = dynamic_cast<Minion *>(it);
				temp->use_ability(player);
				temp = nullptr;
				delete temp;
			}
		}	
	
	} else if ( type == "enter" ) {
		if ( this->get_ritual() != nullptr ) {
                        if ( this->get_ritual()->get_name() == "Aura of Power" ) {
                                Ritual* temp = dynamic_cast<Ritual*>(this->get_ritual());
                                temp->use_ability(player, temp->get_ability());
                                temp = nullptr;
                                delete temp;
                        }
                }

		if (player->getOpp()->getBoard()->get_ritual() != nullptr) {
                	if (player->getOpp()->getBoard()->get_ritual()->get_name() == "Standstill" ) {
				Ritual* temp = dynamic_cast<Ritual*>(player->getOpp()->getBoard()->get_ritual());
                                temp->use_ability(player, temp->get_ability());
                                temp = nullptr;
                                delete temp;
                        }
		}	
		for (auto it: player->getOpp()->getBoard()->get_field()) {
                        if (it->get_name() == "Fire Elemental" ) {
                                 Minion *temp = dynamic_cast<Minion *>(it);
                                 temp->use_ability(player->getOpp());
                                 temp = nullptr;
                                 delete temp;
                        }
                }	

	}
	



}

