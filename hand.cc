#include "hand.h"
using namespace std;

int Hand::getSize() const{
    return cards.size();
}

vector<Card> Hand::getHand() const{
    return cards;
}

Card Hand::getCard( unsigned int i ) const{
    return cards.at(i);
}

void Hand::add( Card card ){
    if(cards.size() < maxSize){
        cards.emplace_back(card);
    }
    else{
        cout << "Hand already full." << endl;
    }
}

void Hand::remove( unsigned int i ){
    cards.erase( cards.begin() + i);
}
