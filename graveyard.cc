#include "graveyard.h"
using namespace std;

Card* Graveyard::revive(){
    Card* temp = grave.back();

    grave.pop_back();

    return temp;
}

Card* Graveyard::top(){
    return grave.back();
}

void Graveyard::add( Card* card ){
    grave.emplace_back( card );
}

int Graveyard::getSize(){
    return grave.size();
}
