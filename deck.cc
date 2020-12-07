#include "deck.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <random>
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
        this->add(i);
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
    Card temp = cards.back();
    cards.pop_back();
    return temp;
}

void Deck::remove(Card card) {
    for (auto it = cards.begin(); it != cards.end(); it++) {
        if (*it == card) {
            cards.erase(it);
            break;
        }
    }
}

void Deck::add(string cardname) {

}