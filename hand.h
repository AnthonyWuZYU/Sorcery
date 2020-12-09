#ifndef HAND_H
#define HAND_H
#include "card.h"
#include <vector>

class Hand{
    std::vector<Card> cards; // The Vector that stores the cards in a hand
    std::size_t maxSize = 5; // The maximum size of the hand

    public:

    int getSize(); // returns the size of the cards vector

    std::vector<Card> getHand(); // returns the vector

    void add(Card card); // adds a card object into the cards vector if it is not full
 
    void remove(Card card); // removes a card object from the cards vector
};

#endif
