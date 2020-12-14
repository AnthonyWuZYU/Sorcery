#include "player.h"
using namespace std;

Player::Player(): life{20}, maxMagic{}, magic{3}, name{""}, board{nullptr}, opponent{nullptr}
{}

Player::Player( string name ): life{20}, magic{3}, name{name}, board{nullptr}, opponent{nullptr}
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
    if (board->get_hand()->getSize() <= 5) {
        board->add_to_hand(board->draw_from_deck());
    } else {
        cout << "Your hand is full, a card was not drawn." << endl;
    }
}

void Player::play_card(unsigned int i) {
    if (board->get_hand()->getSize() > i) {
        Card *card = board->get_hand()->getCard(i);
        int magic_cost = card->get_cost();
    
        if (magic - magic_cost >= 0) { 
            if (card->get_type() == "Minion") {
                board->add_to_field(board->remove_from_hand(i));
            } else if (card->get_type() == "Ritual") {
                board->set_ritual(board->remove_from_hand(i));
            }
        } else {
            cout << "You do not have enough magic to play this card!" << endl;
        }
        magic -= magic_cost;
        card = nullptr;
        delete card;
    } else {
        cout << "There is no card at that index." << endl;
    }
}

void Player::minion_attack(unsigned int i, unsigned int j) {
    if (i < board->get_field().size()) {
        Minion* attacker = dynamic_cast<Minion *>(board->get_card_field(i));
        if (j == 1000) {
        //We attack the opposing the player
        attacker->attack_target(opponent);
        } else {
            //We are attacking another minion
            if (j < opponent->getBoard()->get_field().size()) {
                attacker->attack_target(opponent->getBoard()->get_card_field(j));
            } else {
                cout << "There is no target minion at that index." << endl;
            }
        }
    } else {
        cout << "There is no minion at that index." << endl;
    }
    
    
}
