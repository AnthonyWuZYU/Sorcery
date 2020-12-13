#ifndef HAND_H
#define HAND_H
#include <iostream>
#include <vector>
#include "card.h"

class Hand{
    std::vector<Card> cards; // The Vector that stores the cards in a hand
    std::size_t maxSize = 5; // The maximum size of the hand

    public:

    int getSize() const; // returns the size of the cards vector

    std::vector<Card> getHand() const; // returns the vector

    Card getCard(unsigned int i) const; // returns the card at the specified index i

    void add(Card card); // adds a card object into the cards vector if it is not full. Returns a message
                        // if the hand is already full. 
 
    void remove(unsigned int i); // removes a card object from the cards vector at the specified index i

    ostream& operator<<(ostream &os);
};

#endif
