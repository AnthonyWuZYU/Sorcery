#include "player.h"
using namespace std;

Player::Player(): life{20}, magic{0}, name{""}, deck{nullptr}, hand{nullptr}
{}

Player::Player( string name ): life{20}, magic{0}, name{name}, deck{nullptr}, hand{nullptr}
{}

Player::~Player()
{
    delete hand;
    delete deck;
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

void Player::setHand( Hand *h){
    hand = h;
}
