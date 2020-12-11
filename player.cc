#include "player.h"
using namespace std;

Player::Player(): life{20}, maxMagic{}, magic{0}, name{""}, deck{nullptr}, hand{nullptr}, opponent{nullptr}
{}

Player::Player( string name ): life{20}, magic{0}, name{name}, deck{nullptr}, hand{nullptr}, opponent{nullptr}
{}

Player::~Player()
{
    delete hand;
    delete deck;
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

void Player::setMaxMagic( int m ){
    maxMagic = m;
}

string Player::getName(){
    return name;
}

void Player::setName( string n ){
    name = n;
}

Deck* Player::getDeck(){
    return deck;
}

void Player::setDeck( Deck *d ){
    deck = d;
}

Hand* Player::getHand(){
    return hand;
}

void Player::setHand( Hand *h ){
    hand = h;
}

void Player::setOpp( Player *opp ) {
	opponent = opp;
}

Player* Player::getOpp() {
        return opponent;
}
