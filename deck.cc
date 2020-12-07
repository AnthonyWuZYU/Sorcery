#include "deck.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <stdexcept>

using namespace std;

Deck::Deck(string filename) {
    ifstream infile{ filename };
    string i;
    // Reading the .deck file and adding each card by its name
    while ( true ) {
        infile >> i;
        if ( infile.fail() ) break;
        this.add(i);
    }
}

void Deck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    for ( int i = 0; i < 1000; i++ ) {
		std::shuffle( cards.begin(), cards.end(), rng );	
	} 
}

Card Deck::get_top() {
    return cards.back();
}

Card Deck::pop() {
    
}

void Deck::remove(Card card) {

}

void Deck::add(String cardname) {

}