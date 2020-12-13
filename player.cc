#include "player.h"
using namespace std;

Player::Player(): life{20}, maxMagic{}, magic{3}, name{""}, board{nullptr}, opponent{nullptr}
{}

Player::Player( string name ): life{20}, magic{3}, name{name}, board{nullptr}, opponent{nullptr}
{}

Player::~Player()
{
    delete board;
    delete opponent;
}

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
    board->move_to_hand(board->draw_from_deck());
}

void Player::play_card(unsigned int i) {
    board->move_to_field(board->remove_from_hand(i));
}


