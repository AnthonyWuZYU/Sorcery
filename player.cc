#include "player.h"
using namespace std;

Player::Player(): life{20}, maxMagic{3}, magic{3}, name{""}
{}

Player::Player( string name ): life{20}, maxMagic{3},  magic{3}, name{name}
{}

Player::~Player()
{}

int Player::getLife(){
    return life;
}

void Player::setLife( int l ){
    life = l;
}

int Player::getMagic(){
    return magic;
}

void Player::setMagic( int m ){
    magic = m;
}

int Player::getMaxMagic(){
    return maxMagic;
}

void Player::addMaxMagic( int m ){
    maxMagic += m;
}

string Player::getName(){
    return name;
}

void Player::setName( string n ){
    name = n;
}


Board* Player::getBoard(){
    return board;
}

void Player::setBoard(Board* board) {
    this->board = board;
}

void Player::setOpp( Player *opp ) {
        opponent = opp;
}

Player* Player::getOpp() {
        return opponent;
}

void Player::draw(){
    int size = board->get_hand()->getSize();
    int max_size = board->get_hand()->maxSize;
    if (size < max_size) {
        Card *temp = board->draw_from_deck();
        if (!temp) {
            cout << "You have no cards left in your deck, a card was not drawn." << endl;
        } else {
            board->add_to_hand(temp);
        }
        temp = nullptr;
        delete temp;
    } else {
        cout << "Your hand is full, a card was not drawn." << endl;
    }
}

void Player::play_card(unsigned int i, bool test) {
    unsigned int size = board->get_hand()->getSize();
    if (size > i) {
        Card *card = board->get_hand()->getCard(i);
        int magic_cost = card->get_cost();
    
        if (magic - magic_cost >= 0 || test) { 
            if (card->get_type() == "Minion") {
                board->add_to_field(this, board->remove_from_hand(i));
		magic -= magic_cost;
        	if (magic < 0) magic = 0;
            } else if (card->get_type() == "Ritual") {
                board->set_ritual(board->remove_from_hand(i));
		magic -= magic_cost;
        	if (magic < 0) magic = 0;
            } else if (card->get_type() == "Enchant") {
		int p;
                unsigned int pos = 7;
                cin >> p;
		cin >> pos;
		if (p == 1) {
			
                	Card* temp = board->get_card_field(pos-1);
                	if (!temp) {
                    	cout << "There is no Minion at that index!" << endl;  
                	} else {
                	    Minion* target = dynamic_cast<Minion *>(temp);
                	    Enchant* enchantment = dynamic_cast<Enchant *>(board->remove_from_hand(i));
                	    target->enchant(enchantment);
			    magic -= magic_cost;
        		    if (magic < 0) magic = 0;
			    this->is_dead(pos-1, board);
                	}
		 } else if (p == 2) {
		 	Card* temp = opponent->getBoard()->get_card_field(pos-1);
                        if (!temp) {
                        cout << "There is no Minion at that index!" << endl;
                        } else {
                            Minion* target = dynamic_cast<Minion *>(temp);
                            Enchant* enchantment = dynamic_cast<Enchant *>(board->remove_from_hand(i));
                            target->enchant(enchantment);
                            magic -= magic_cost;
                            if (magic < 0) magic = 0;
			}
		 } else {
		 	cerr << "Invalid player" << endl;
		 }	
            } else if (card->get_type() == "Spell") {
                Spell* spell = dynamic_cast<Spell *>(board->get_card_hand(i));
                if (spell->use_ability(this, spell->get_ability())) {
                    board->remove_from_hand(i);
                }

            }
	} else {
            cout << "You do not have enough magic to play this card!" << endl;
        }
        card = nullptr;
        delete card;
    } else {
        cout << "There is no card at that index." << endl;
    }
}

void Player::minion_attack(unsigned int i, unsigned int j) {
    // Check if i is in range
    if (i < board->get_field().size()) {
        Minion* attacker = dynamic_cast<Minion *>(board->get_card_field(i));
        if (j == 1000) {
        //We attack the opposing the player
            attacker->attack_target(opponent);
	    attacker->set_action(0);
        } else {
            //We are attacking another minion

            // Check if j is in range
            if (j < opponent->getBoard()->get_field().size()) {
                attacker->attack_target(opponent->getBoard()->get_card_field(j));
                is_dead(j, opponent->getBoard());
                is_dead(i, board);
		attacker->set_action(0);
            } else {
                cout << "There is no target minion at that index." << endl;
            }
        }
        attacker = nullptr;
        delete attacker;
    } else {
        cout << "There is no minion at that index." << endl;
    }
}

void Player::reset_action() {
    Minion *temp;
    bool delay = false;
    unsigned int index = 0;
    for (auto it: board->get_field()) {
        temp = dynamic_cast<Minion *>(it);
	for (auto en: temp->get_enchant()) {
		if (en->get_name() == "Delay") {
			delay = true;
			break;
		}
		index++;
	}
        if (!delay) {
	       temp->set_action(1);
	} else {
		vector<Card *> temp_e = temp->get_enchant();
		temp_e.erase(temp_e.begin() + index);
		temp->set_enchant(temp_e);
	}
    }
    temp = nullptr;
    delete temp;
}

void Player::is_dead(unsigned int i, Board* board) {
    Minion *temp = dynamic_cast<Minion *>(board->get_card_field(i));
	
    if (temp->get_defence() <= 0) {
	if (temp->get_name() == "Bomb") {
		temp->use_ability(this);
	}
	
        board->add_to_graveyard(board->remove_from_field(i));
        cout << temp->get_name() << " has been sent to the graveyard!" << endl;
    }
    temp = nullptr;
    delete temp;

}
