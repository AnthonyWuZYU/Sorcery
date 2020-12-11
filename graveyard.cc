#include "graveyard.h"

Card Graveyard::revive(){
    Card temp = grave.back();

    grave.pop_back();

    return temp;
}

Card Graveyard::top(){
    return grave.back();
}

void Graveyard::add( Card card ){
    grave.emplace_back( card );
}
