#include "hand.h"
using namespace std;

int Hand::getSize() const{
    return cards.size();
}

vector<Card*> Hand::getHand() const{
    return cards;
}

Card* Hand::getCard( unsigned int i ) const{
    return cards.at(i);
}

void Hand::add( Card* card ){
    cards.emplace_back(card);
}

void Hand::remove( unsigned int i ){
    cards.erase( cards.begin() + i);
}

std::ostream& operator<<(std::ostream &os, const Hand &hand) {
    for (auto it : hand.getHand()) {
        it->print(os);
    }
    return os;
}
