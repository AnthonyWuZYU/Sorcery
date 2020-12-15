#ifndef GRAVEYARD_H
#define GRAVEYARD_H
#include <iostream>
#include <vector>
#include "card.h"

class Graveyard{
    std::vector<Card*> grave; // The Vector that stores the dead cards of a player

    public:

    Card* revive(); // returns the top card ( most recent dead card ) and removes it from the vector grave

    Card* top(); // returns the top card ( most recent dead card ) from the vector grave

    void add( Card* card ); // adds a dead card to the vector grave

    int getSize(); // returns grave vector's size
};

#endif

